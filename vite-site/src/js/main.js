import {WASM} from './wasm/wasm.js'
import { primes } from './primes.js'


document.getElementById("hello_wasm").onclick = function(){
	WASM.hello_wasm();
}

function compute(work){
	let val = 0;
	let prime_count = 100000;//max 100000
	let ptr = WASM.malloc(prime_count*4);
	
	let data_view = WASM.ui32(ptr,prime_count);
	data_view.set(new Uint32Array(primes.buffer,0,prime_count));

	let then = performance.now();

	val = work(ptr,prime_count);

	let dt = (performance.now() - then);//convert ms->ns

	console.log(primes.length);

	document.getElementById("result").innerHTML = "The first "+ prime_count + " primes sum up to " + val + "<br>Took " + (dt) + "ms";
	WASM.free(ptr);
}
document.getElementById("compute_branch").onclick = ()=>compute(WASM.compute_branch);
document.getElementById("compute_goodbranch").onclick = ()=>compute(WASM.compute_branch_predict);
document.getElementById("compute_branchless").onclick = ()=>compute(WASM.compute_branchless);

document.getElementById("compute_wasm").onclick = ()=>compute(WASM.compute_add);
document.getElementById("compute_wasm_vec").onclick = ()=>compute(WASM.compute_add_vec);
document.getElementById("compute_wasm_unrolled").onclick = ()=>compute(WASM.compute_add_unrolled);
document.getElementById("compute_js").onclick = ()=>compute((ptr,prime_count)=>{
	let sum = 0;
	for(let i = 0; i < prime_count; i++){
		sum += primes[i];
	}
	return sum;
});

