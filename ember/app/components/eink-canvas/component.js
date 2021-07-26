import Component from '@glimmer/component';
import { tracked } from '@glimmer/tracking';
import { action } from '@ember/object';
import { inject as service } from '@ember/service';

export default class EinkCanvasComponent extends Component {
  @service
  bmp;

  @tracked
  darkDataUrl;

  @tracked
  yellowDataUrl;

  @tracked
  ready;

  @action
  setupCanvas(canvas) {
    this.canvas = canvas;
    this.context = canvas.getContext('2d');
    this.context.fillStyle = 'white';
    this.context.fillRect(0, 0, 240, 416);
    this.context.font = '42px serif';
    this.context.fillStyle = 'black';
    this.context.fillText(
      `it's ${Math.floor(this.args.data.current.temp)}°`,
      10,
      50
    );
    if (
      Math.abs(
        this.args.data.current.temp - this.args.data.current.feels_like
      ) > 5
    ) {
      this.context.font = '24px serif';
      this.context.fillText('but it feels like', 10, 90);
      this.context.font = '42px serif';
      this.context.fillText(`${this.args.data.current.feels_like}°`, 60, 140);
    }
    let icon = this.args.data.current.weather.firstObject.icon;
    let url = `https://openweathermap.org/img/wn/${icon}.png`;
    let image = new Image();
    image.crossOrigin = 'anonymous'; // This enables CORS
    image.onload = () => {
      this.context.drawImage(image, 240 / 2 - 100, 200, 200, 200);
      this.darkDataUrl =
        'data:image/bmp;base64,' + btoa(this.bmp.createBMP(this.canvas));
      this.yellowDataUrl =
        'data:image/bmp;base64,' + btoa(this.bmp.createYellowBMP(this.canvas));
      this.ready = true;
    };
    image.src = url;
  }

  @action
  download(event) {
    // let currentDate = new Date();
    // let cDay = currentDate.getDate();
    // let cMonth = currentDate.getMonth() + 1;
    // let cYear = currentDate.getFullYear();
    //event.target.download = `${cYear}.${cMonth}.${cDay}.bmp`;
    event.target.download = `dark.bmp`;
    event.target.href = this.darkDataUrl;
  }
}
