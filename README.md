# Search Engine in C++

Building a search engine from scratch in modern C++.

Started: July 2026

<div align="center">

# SearchEngineCPP

### A Full-Stack Document Search Engine built from scratch in **C++**

Search through TXT and PDF documents using a custom-built search engine implementing an **Inverted Index**, **Trie**, **TF-IDF Ranking**, **Boolean Query Parsing**, **Phrase Search**, **Fuzzy Search**, and **Snippet Generation**.

React • Express • C++

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![React](https://img.shields.io/badge/React-Frontend-61DAFB)
![Express](https://img.shields.io/badge/Express-Backend-green)
![License](https://img.shields.io/badge/License-MIT-orange)

</div>

---

# Overview

SearchEngineCPP is a search engine that indexes user-uploaded documents and retrieves the most relevant results using classical Information Retrieval algorithms.

Unlike applications that rely on existing search libraries, this project implements the core search algorithms from scratch in C++.

The frontend and backend act only as an interface—the actual search engine is completely implemented in C++.

---

# Features

## Document Support

- TXT Documents
- PDF Documents (automatic text extraction)

---

## Search Features

- Keyword Search
- Multi-word Search
- Phrase Search
- Boolean Queries
  - AND
  - OR
  - NOT
- Ranked Search (TF-IDF)
- Multi-word Autocomplete
- Fuzzy Search (Levenshtein Distance)
- Search Suggestions

---

## Result Features

- Ranked Results
- Keyword Highlighting
- Context Snippet Generation
- Filename Display

---

# Architecture

```text
                 React Frontend
                        │
                  HTTP Requests
                        │
                Express Backend
                        │
           PDF → Text Conversion
                        │
                SearchEngine.exe
                        │
      ┌────────────────────────────┐
      │       Search Engine         │
      │                             │
      │  Tokenizer                  │
      │  Inverted Index             │
      │  Trie                       │
      │  Query Parser               │
      │  Boolean Evaluator          │
      │  TF-IDF Ranker              │
      │  Fuzzy Search               │
      │  Snippet Generator          │
      └────────────────────────────┘
```
<img width="2334" height="1824" alt="Gemini_Generated_Image_nmali3nmali3nmal" src="https://github.com/user-attachments/assets/50a7abb5-3dcc-4228-95d3-63bd04bbb578" />



---

# Algorithms Implemented

## Tokenization

- Lowercasing
- Punctuation Removal
- Word Extraction

---

## Inverted Index

Stores

```text
word
   ↓
document id
   ↓
positions
```

Example

```text
compiler

↓

Document 2 → [15,29]
Document 5 → [4,18]
Document 9 → [91]
```

---

## Trie

Used for

- Prefix Search
- Autocomplete
- Multi-word Autocomplete

Time Complexity

```text
O(length of prefix)
```

---

## TF-IDF Ranking

Ranking Score

```text
TF = termFrequency / documentLength

IDF = log(totalDocuments / documentFrequency)

Score = TF × IDF
```

Documents are sorted by decreasing score.

---

## Boolean Query Parsing

Supports

```text
compiler AND design

compiler OR parser

compiler AND NOT parser
```

using an Abstract Syntax Tree.

---

## Phrase Search

Supports

```text
"machine learning"

"compiler design"
```

using positional indexes.

---

## Fuzzy Search

Implemented using Levenshtein Distance.

Example

```text
compilor

↓

compiler
```

---

## Snippet Generation

Displays a small portion of text around the matched keyword.

Example

```text
...Explain the phases of a compiler by translating...
```

---

# Project Structure

```text
SearchEngineCPP/

│
├── backend/
│   ├── controllers/
│   ├── routes/
│   ├── services/
│   └── uploads/
│
├── frontend/
│   ├── src/
│   └── public/
│
├── data/
│
├── tokenizer/
├── index/
├── search/
├── models/
│
└── main.cpp
```

---

# How it Works

1. Upload TXT or PDF documents.
2. PDFs are converted into plain text.
3. The C++ engine indexes every document.
4. Queries are parsed.
5. TF-IDF scores are computed.
6. Results are ranked.
7. Snippets are generated.
8. Matching keywords are highlighted.

---

# Tech Stack

### Frontend

- React
- CSS

### Backend

- Node.js
- Express
- Multer

### Core Engine

- Modern C++17
- STL

---

# Screenshots

## Home

> <img width="1392" height="772" alt="home page engine" src="https://github.com/user-attachments/assets/078f9cef-11ff-404f-832f-53ce02f49ce7" />


---

## Upload

> <img width="1261" height="302" alt="upload engine" src="https://github.com/user-attachments/assets/cb12fd68-2374-4cf9-97e7-edbbd0ed4bbd" />


---

## Search Results

> <img width="1345" height="702" alt="search engine" src="https://github.com/user-attachments/assets/beb10261-39aa-4bf4-990e-f8add8a8de93" />


---

## Highlighting

> <img width="305" height="197" alt="highlight engine" src="https://github.com/user-attachments/assets/3771efb8-88fc-441a-8a7f-738dc1bc17de" />


---

# Complexity

| Component | Complexity |
|------------|------------|
| Tokenization | O(n) |
| Index Construction | O(total words) |
| Trie Search | O(prefix length) |
| Boolean Search | O(result size) |
| Phrase Search | O(total positions) |
| TF-IDF Ranking | O(m log m) |
| Fuzzy Search | O(dictionary × word length²) |

---

# Future Improvements

- BM25 Ranking
- Incremental Indexing
- Stop-word Removal
- Stemming
- Wildcard Queries
- Parallel Index Construction
- Persistent Index Storage

---

# Key Learnings

While building this project, I learned

- Information Retrieval
- Search Engine Architecture
- Trie Data Structure
- TF-IDF Ranking
- Levenshtein Distance
- Boolean Query Parsing
- React ↔ Express ↔ C++ Integration
- File Upload Pipelines
- PDF Text Extraction

---

# Why This Project?

Most search applications use existing search libraries such as Elasticsearch or Lucene.

The goal of this project was different.

The objective was to understand how a search engine works internally by implementing the core algorithms from scratch.

---
