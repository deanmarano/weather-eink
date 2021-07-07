import Route from '@ember/routing/route';

export default class IndexRoute extends Route {
  async model() {
    let request = await fetch("https://api.openweathermap.org/data/2.5/onecall?lat=42.95478577692492&lon=-85.63894466729519&APPID=7517f45cadbf945821e6e32fc341d6f4&units=imperial&exclude=minutely");
    return request.json();
  }
}
