'use strict';
const ZUC = require('./zuc');
const assert = require('assert');

const iv = new Uint8Array(16);
const key = new Uint8Array(16);
const buffer = new Uint32Array(1024 * 1024 / Uint32Array.BYTES_PER_ELEMENT); // 1 MiB buffer.
for (let i = 0; i < iv.length; ++i) {
  iv[i] = 0;
  key[i] = 0;
}


const zuc = new ZUC(key, iv);
zuc.generateKeystream(buffer);
assert.strictEqual('27bede74, 18082da', `${buffer[0].toString(16)}, ${buffer[1].toString(16)}`);
console.log('Correct ZUC output.');

const LOOP_LIMIT = (1024 * 1024 * 1024) / (Uint32Array.BYTES_PER_ELEMENT * buffer.length); // 1 GiB.
const timeStarted = Date.now();
for (let i = 0; i < LOOP_LIMIT; ++i) {
  zuc.generateKeystream(buffer);
}

const timeUsed = Date.now() - timeStarted;
console.log(`Generates ZUC keystream at ${1024 * 1000 / timeUsed} MiB/s.`);
