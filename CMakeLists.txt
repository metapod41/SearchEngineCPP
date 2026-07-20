cmake_minimum_required(VERSION 3.16)

project(SearchEngineCPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(SearchEngine

    main.cpp

    models/Document.cpp

    tokenizer/Tokenizer.cpp

    index/InvertedIndex.cpp
    index/Trie.cpp
    index/FuzzySearch.cpp

    search/QueryParser.cpp
    search/SearchEngine.cpp
    search/SnippetGenerator.cpp
)