import { printf_imports } from "./imports/printf";


const memory = new WebAssembly.Memory({
	initial: 2,
	maximum: 100
});

const importFunctions = Object.freeze({
    memory: memory,
	...printf_imports
});

const wasmImport = {
    env: importFunctions,
    js: { }
};

console.log(wasmImport.env)

export const WASM = await WebAssembly.instantiateStreaming(fetch("src/assets/program.wasm"), wasmImport).then((module)=>{
	const exp = module.instance.exports;
	return {
		/**
		 * ADD YOUR EXPORTED FUNCTIONS HERE
		 */

		hello_wasm: exp.hello_wasm,
		compute_add: exp.compute_add,
		compute_add_vec: exp.compute_add_vec,
		compute_add_unrolled: exp.compute_add_unrolled,

		compute_branch: exp.compute_branch,
		compute_branch_predict: exp.compute_branch_predict,
		compute_branchless: exp.compute_branchless,
		//=================================

		rawmem: memory,
		
		malloc: exp.malloc,
		free: exp.free,

		ascii_decoder: new TextDecoder('ascii'),
		raw: function(){
			return this.rawmem;
		},
		bytes: function(){
			return this.rawmem.buffer.byteLength;
		},
		ui8: function(pointer, len){
			return new Uint8Array(this.rawmem.buffer, pointer, len);
		},
		ui16: function(pointer, len){
			return new Uint16Array(this.rawmem.buffer, pointer, len);
		},
		ui32: function(pointer, len){
			
			return new Uint32Array(this.rawmem.buffer, pointer, len);
		},
		ui64: function(pointer, len){
			return new BigUint64Array(this.rawmem.buffer, pointer, len);
		},
		i8: function(pointer, len){
			return new Int8Array(this.rawmem.buffer, pointer, len);
		},
		i16: function(pointer, len){
			return new Int16Array(this.rawmem.buffer, pointer, len);
		},
		i32: function(pointer, len){
			return new Int32Array(this.rawmem.buffer, pointer, len);
		},
		i64: function(pointer, len){
			return new BigInt64Array(this.rawmem.buffer, pointer, len);
		},
		f32: function(pointer, len){
			return new Float32Array(this.rawmem.buffer, pointer, len);
		},
		f64: function(pointer, len){
			return new Float64Array(this.rawmem.buffer, pointer, len);
		},
		string: function(pointer,len){
			return this.ascii_decoder.decode(new Uint8Array(this.rawmem.buffer, pointer, len));
		},
		view_ui8: function(){
			return new Uint8Array(this.rawmem.buffer, 0, this.rawmem.buffer.byteLength);
		}
	}
});