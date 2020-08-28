const express = require("express");
const bodyParser = require("body-parser");
const execFile = require("child_process").execFile;

const app = express();

app.use(bodyParser.json());

app.use((req, res, next) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Methods", "GET, POST");
    res.setHeader(
        "Access-Control-Allow-Headers",
        "Content-Type, Authorization"
    );
    next();
});

app.post("/smp", (req, res) => {
    const child = execFile("./smp", function (error, stdout) {
        //just \n on unix
        const result = stdout.split("\n");

        res.status(201).json(result);
    });

    const preferences = req.body;
    child.stdin.write("run\n");
    let numItems = preferences[0].toString();
    child.stdin.write(numItems);
    child.stdin.write("\n");
    for (let i = 1; i <= preferences[0] * 2; i++) {
        let toWrite = preferences[i].toString().replace(/,/g, " ");
        //console.log(toWrite);
        child.stdin.write(toWrite);
        child.stdin.write("\n");
    }
});

const port = process.env.PORT || 8080;
app.listen(port);
