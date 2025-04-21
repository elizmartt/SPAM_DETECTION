cmake_minimum_required(VERSION 3.25)
project(spam_detection)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(spam_detection
        main.cpp
        src/TfidfVectorizer.cpp
        src/LogisticRegression.cpp
        src/DataLoader.cpp
)
