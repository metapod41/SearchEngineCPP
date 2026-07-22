import { useState } from "react";
import "./App.css";

function App() {
  const [query, setQuery] = useState("");
  const [result, setResult] = useState("");
  const [files, setFiles] = useState([]);
  const [message, setMessage] = useState("");

  async function search() {
    try {
      const response = await fetch(
        `http://localhost:3000/search?q=${encodeURIComponent(query)}`
      );

      const data = await response.json();

      if (data.success) {
        setResult(data.output);
      } else {
        setResult(data.error);
      }
    } catch {
      setResult("Cannot connect to backend.");
    }
  }

  async function uploadFiles() {
    if (files.length === 0) {
      setMessage("Please choose files first.");
      return;
    }

    const formData = new FormData();

    for (let file of files) {
      formData.append("documents", file);
    }

    try {
      const response = await fetch("http://localhost:3000/upload", {
        method: "POST",
        body: formData,
      });

      const data = await response.json();

      if (data.success) {
        setMessage("✅ Files uploaded successfully!");
      } else {
        setMessage("❌ Upload failed.");
      }
    } catch {
      setMessage("Cannot connect to backend.");
    }
  }

  return (
    <div className="container">
      <h1>C++ Search Engine</h1>

      <div className="uploadBox">
        <input
          type="file"
          multiple
          accept=".txt,.pdf"
          onChange={(e) => setFiles([...e.target.files])}
        />

        <button onClick={uploadFiles}>
          Upload
        </button>
      </div>

      <p>{message}</p>

      <div className="searchBox">
        <input
          type="text"
          placeholder="Search..."
          value={query}
          onChange={(e) => setQuery(e.target.value)}
          onKeyDown={(e) => {
            if (e.key === "Enter") search();
          }}
        />

        <button onClick={search}>
          Search
        </button>
      </div>

      <pre
        dangerouslySetInnerHTML={{
          __html: result.replace(
            /\*\*(.*?)\*\*/g,
            "<span class='highlight'>$1</span>"
          ),
        }}
      />
    </div>
  );
}

export default App;