// run a simple burnin script. this doesn't really do anything useful

let count = 25000;

console.log(`Running ${count} iterations!`)
for ( let i = 0; i < count; i++ ) {
  require('./index.js');
}
console.log("Done!");