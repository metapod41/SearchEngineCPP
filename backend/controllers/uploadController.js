const fs = require("fs");
const path = require("path");
const pdf = require("pdf-parse");

async function uploadController(req, res) {

    if (!req.files || req.files.length === 0) {
        return res.status(400).json({
            success: false,
            message: "No files uploaded."
        });
    }

    const uploadDir = path.join(__dirname, "../uploads");

    const indexedFiles = [];

    try {

        for (const file of req.files) {

            const ext = path.extname(file.originalname).toLowerCase();

            
            if (ext === ".txt") {
                indexedFiles.push(file.originalname);
                continue;
            }

            
            if (ext === ".pdf") {

                const buffer = fs.readFileSync(file.path);

                const data = await pdf(buffer);

                const txtName =
                    path.basename(file.originalname, ".pdf") + ".txt";

                fs.writeFileSync(
                    path.join(uploadDir, txtName),
                    data.text
                );

                fs.unlinkSync(file.path);

                indexedFiles.push(txtName);
            }
        }

        res.json({
            success: true,
            files: indexedFiles
        });

    }
    catch (err) {

        console.error(err);

        res.status(500).json({
            success: false,
            message: "PDF parsing failed."
        });
    }
}

module.exports = {
    uploadController
};