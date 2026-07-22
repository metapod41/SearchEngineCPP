const express = require("express");
const router = express.Router();

const multer = require("multer");
const fs = require("fs");
const path = require("path");

const { search } = require("../controllers/searchController");
const { uploadController } = require("../controllers/uploadController");


function clearUploads(req, res, next) {

    const uploadDir = path.join(__dirname, "../uploads");

    if (!fs.existsSync(uploadDir)) {
        fs.mkdirSync(uploadDir);
    }

    const files = fs.readdirSync(uploadDir);

    for (const file of files) {
        fs.unlinkSync(path.join(uploadDir, file));
    }

    next();
}

const storage = multer.diskStorage({

    destination: function (req, file, cb) {
        cb(null, path.join(__dirname, "../uploads"));
    },

    filename: function (req, file, cb) {
        cb(null, file.originalname);
    }

});

const upload = multer({
    storage
});

router.get("/search", search);

router.post(
    "/upload",
    clearUploads,
    upload.array("documents"),
    uploadController
);

module.exports = router;