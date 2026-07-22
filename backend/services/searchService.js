const { spawn } = require("child_process");
const path = require("path");

function search(query) {
    return new Promise((resolve, reject) => {

        const exePath = path.join(__dirname, "../../SearchEngine.exe");

        const cpp = spawn(exePath, [], {
        cwd: path.join(__dirname, "../..")
        });

        let output = "";
        let error = "";

        cpp.stdout.on("data", (data) => {
            output += data.toString();
        });

        cpp.stderr.on("data", (data) => {
            error += data.toString();
        });

        cpp.on("close", (code) => {

            if (code !== 0) {
                reject(error);
                return;
            }

            resolve(output);
        });

        cpp.stdin.write(query + "\n");
        cpp.stdin.end();

    });
}

module.exports = {
    search
};