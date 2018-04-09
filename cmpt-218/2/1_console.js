console.log("hello1");
// console.warn("don't do that!");
// console.info("running app ...");

console.time('flag');
process.nextTick(function(){
  console.log(console.timeEnd('flag'));
});

console.log("hello2");
