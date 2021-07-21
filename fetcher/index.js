console.log('*****index.js*****');
console.log('Requiring puppeteer');
const puppeteer = require('puppeteer-core');

async function main() {
  try {
    console.log('Starting the browser...');
    const browser = await puppeteer.launch({
      executablePath: '/usr/bin/chromium-browser',
      args: ['--no-sandbox']
    });
    const page = await browser.newPage();
    await page.setCacheEnabled(false);
    await page._client.send('Page.setDownloadBehavior', {behavior: 'allow', downloadPath: './downloads'});
    console.log('Loading the page...');
    await page.goto("http://192.168.1.6:4200", { waitUntil: 'networkidle2' });
    console.log('Clicking the link...');
    await page.click("a");
    console.log('Downloading...');
    await page.waitFor(10000);
    browser.close();
    console.log('Done! Browser closed.');
    process.exit(0);
  } catch(e) {
    console.error(`Oh no! Something went wrong.`);
    console.error(e);
    process.exit(1);
  }
}
main();
