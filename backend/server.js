const express = require("express");
const searchRoutes = require("./routes/searchRoutes");
const cors = require("cors");
const path = require("path");

const app = express();

app.use(cors());
app.use(express.json());

app.use("/uploads", express.static(path.join(__dirname, "uploads")));

const PORT = 3000;

app.get("/", (req, res) => {
    res.send("Backend Working");
});

app.use(searchRoutes);

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});