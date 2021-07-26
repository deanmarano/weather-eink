import Service from '@ember/service';

export default class BmpService extends Service {
  createBMP(canvas) {
    var context = canvas.getContext('2d');
    var width = canvas.width;
    var height = canvas.height;
    var imageData = context.getImageData(0, 0, width, height);
    var data = imageData.data;

    //create pixel array from canvas based on alpha
    var pixels = [];
    for (var i = data.length; i > 0; i -= 4) {
      if (i > 0) {
        if (
          data[i - 2] > 200 &&
          !(data[i] < 240 && data[i + 1] < 235 && data[i + 2] < 220)
        ) {
          pixels.push('ffffff');
        } else {
          pixels.push('000000');
        }
      }
    }

    //unmirror
    var pixarray = [];
    for (i = height - 1; i > -1; i--) {
      var row = [];
      for (var j = 0; j < width; j++) {
        row.push(pixels[i * width + j]);
      }
      for (j in row) {
        pixarray.push(row[j]);
      }
    }
    pixarray.reverse();

    return this.bmp_mono(width + 1, height, pixarray);
  }

  isDark(data, i) {
    return 220 > data[i] && 220 > data[i + 1] && 220 > data[i + 2];
  }

  isLight(data, i) {
    return 220 < data[i] && 220 < data[i + 1] && 220 < data[i + 2];
  }

  createYellowBMP(canvas) {
    var context = canvas.getContext('2d');
    var width = canvas.width;
    var height = canvas.height;
    var imageData = context.getImageData(0, 0, width, height);
    var data = imageData.data;

    //create pixel array from canvas based on alpha
    var pixels = [];
    for (var i = data.length; i > 0; i -= 4) {
      if (i > 0) {
        if (!this.isDark(data, i) && !this.isLight(data, i)) {
          pixels.push('000000');
        } else {
          pixels.push('ffffff');
        }
      }
    }

    //unmirror
    var pixarray = [];
    for (i = height - 1; i > -1; i--) {
      var row = [];
      for (var j = 0; j < width; j++) {
        row.push(pixels[i * width + j]);
      }
      for (j in row) {
        pixarray.push(row[j]);
      }
    }
    pixarray.reverse();

    return this.bmp_mono(width + 1, height, pixarray);
  }
  /*
Create an uncompressed Windows bitmap (monochrome) given width, height and an
array of pixels.

Pixels should be in BMP order, i.e. starting at the bottom left, going up
one row at a time.
*/
  bmp_mono(width, height, pixarray, palette) {
    var rowsize = Math.ceil(width / 8);
    var rowpadding = 4 - (rowsize % 4);
    if (typeof palette == 'undefined') palette = ['000000', 'ffffff'];

    var j, pix, mod;
    pixarray.reverse();
    var pixels = [];
    var b = 0;
    for (var i = 0; i < height; ++i) {
      for (j = 0; j < width; ++j) {
        mod = j % 8;
        pix = pixarray.pop();
        if (parseInt(pix, 16) != 0) {
          b = b | Math.pow(2, 7 - mod);
        }
        if (mod == 7 || j == width - 1) {
          pixels.push(String.fromCharCode(b));
          b = 0;
        }
      }
      for (j = 0; j < rowpadding; ++j) {
        pixels.push('\x00');
      }
    }
    return this._bmp(width, height, palette, pixels.join(''), 1, 0);
  }

  _bmp(width, height, palette, imgdata, bpp, compression) {
    var imgdatasize = imgdata.length;
    var palettelength = palette.length;
    var palettesize = palettelength * 4; // 4 bytes per colour
    var pixeloffset = 54 + palettesize; // pixel data offset
    var data = [
      'BM', // magic number
      this._pack(width), // size of file
      '\x00\x00\x00\x00', // unused
      this._pack(pixeloffset), // number of bytes until pixel data
      '\x28\x00\x00\x00', // number of bytes left in the header
      this._pack(width), // width of pixmap
      this._pack(height), // height of pixmap
      '\x01\x00', // number of colour planes, must be 1
      this._pack(bpp, 2), // bits per pixel
      this._pack(compression), // compression mode
      this._pack(imgdatasize), // size of raw BMP data (after the header)
      '\x13\x0B\x00\x00', // # pixels per metre horizontal res.
      '\x13\x0B\x00\x00', // # pixels per metre vertical res
      this._pack(palettelength), // num colours in palette
      '\x00\x00\x00\x00', // all colours are important
      // END OF HEADER
    ];

    for (var i = 0; i < palette.length; ++i) {
      data.push(this._pack(parseInt(palette[i], 16)));
    }
    data.push(imgdata);
    return data.join('');
  }
  /*
Pack JS integer (signed big-endian?) `num` into a little-endian binary string
of length `len`.
*/
  _pack(num, len) {
    var o = [], len = ((typeof len == 'undefined') ? 4 : len);
    for (var i=0; i<len; ++i) {
      o.push(String.fromCharCode((num >> (i * 8)) & 0xff));
    }
    return o.join("");
  }
}
