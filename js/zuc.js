'use strict';
const Module = require('./zuc.asm');

class ZUC {
  /**
   * @param {Uint8Array} key - 128-bits key for ZUC.
   * @param {Uint8Array} iv - 128-bits initialization vector for ZUC.
   */
  constructor(key, iv) {
    this._pContext = Module._malloc(88);
    this._pKey = Module._malloc(key.length * key.BYTES_PER_ELEMENT);
    this._pIv = Module._malloc(iv.length * iv.BYTES_PER_ELEMENT);
    Module.HEAPU8.set(key, this._pKey);
    Module.HEAPU8.set(iv, this._pIv);
    Module._zuc_init(this._pContext, this._pKey, this._pIv);
    Module._free(this._pKey);
    Module._free(this._pIv);
    delete this._pKey;
    delete this._pIv;
  }

  /**
   * @param {Uint32Array} buffer - Buffer to fill with ZUC keystream.
   * @returns {void}
   */
  generateKeystream(buffer) {
    const pBuffer = Module._malloc(buffer.length * buffer.BYTES_PER_ELEMENT);
    Module._zuc_generate_keystream(this._pContext, pBuffer, buffer.length);
    for (let i = 0; i < buffer.length; ++i) {
      buffer[i] = Module.HEAPU32[pBuffer / 4 + i];
    }
  
    Module._free(pBuffer);
  }

  free() {
    Module._free(this._pContext);
    delete this._pContext;
  }
}

module.exports = ZUC;

