const { search } = require("../services/searchService");

async function searchController(req, res) {

    try {

        const query = req.query.q;

        const output = await search(query);

        res.json({
            success: true,
            output: output
        });

    } catch (err) {

        res.status(500).json({
            success: false,
            error: err.toString()
        });

    }
}

module.exports = {
    search: searchController
};