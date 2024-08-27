cmake_minimum_required(VERSION 3.14)

# Название проекта
project(MyProjectName VERSION 1.0 LANGUAGES CXX)

# Установка версии Qt и необходимых модулей
set(CMAKE_PREFIX_PATH "path_to_qt")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql PrintSupport Widgets)

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

set(SOURCES
    dialogwindow.cpp
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    dialogwindow.h
    mainwindow.h
    connect.h
)

set(FORMS
    mainwindow.ui
    form.ui
    report.ui
)

# Генерация файлов из .ui
qt_wrap_ui(UIC_SOURCES ${FORMS})

# Генерация файлов moc
qt_wrap_cpp(MOC_SOURCES ${HEADERS})

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES} ${UIC_SOURCES})

# Связывание с библиотеками Qt
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Sql Qt6::PrintSupport Qt6::Widgets)

# Установка путей для развёртывания
if(QNX)
    set(DEPLOY_PATH /tmp/${PROJECT_NAME}/bin)
elseif(UNIX AND NOT ANDROID)
    set(DEPLOY_PATH /opt/${PROJECT_NAME}/bin)
endif()

if(DEPLOY_PATH)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${DEPLOY_PATH})
endif()
