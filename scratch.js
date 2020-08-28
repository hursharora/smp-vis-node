// standard node module
const execFile = require("child_process").execFile;

// this launches the executable and returns immediately
let child = execFile("smp.exe", function (error, stdout, stderr) {
    // This callback is invoked once the child terminates
    // You'd want to check err/stderr as well!
    const testarr = stdout.split("\r\n");
    console.log(testarr);
});

// if the program needs input on stdin, you can write to it immediately
//child.stdin.setDefaultEncoding('utf-8');
child.stdin.write("run\n");
child.stdin.write("5\n");
for (let i = 0; i < 10; i++) {
    child.stdin.write("0 1 2 3 4\n");
}
