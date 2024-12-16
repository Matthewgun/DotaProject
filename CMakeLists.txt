cmake_minimum_required(VERSION 3.10)

# Укажите имя проекта
project(Dota2HeroPicker)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавьте исполняемый файл
add_executable(Dota2HeroPicker main.cpp)

# Укажите путь к библиотеке JSON
include_directories("C:/nlohmannjson/include")

# Укажите путь к файлу JSON, если он находится в другом каталоге
configure_file(HeroList.json ${CMAKE_CURRENT_BINARY_DIR}/HeroList.json COPYONLY)
