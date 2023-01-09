cmake_minimum_required(VERSION 3.20)
project(julia_orm)

set(CMAKE_CXX_STANDARD 20)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/fmt/include )


add_executable(julia_orm main.cpp lib/tools/TextIterator.cpp lib/tools/TextIterator.hpp lib/include/TextIndex.hpp lib/tools/Iterator.cpp lib/tools/Iterator.hpp lib/include/schema/Database.hpp lib/include/schema/Entity.hpp lib/include/schema/Field.hpp lib/include/schema/DbSet.hpp lib/include/schema/Value.hpp lib/include/schema/Annotation.hpp lib/parser/Token.hpp lib/parser/Tokenizer.cpp lib/parser/Tokenizer.hpp lib/include/const.hpp lib/parser/SchemaTreeBuilder.cpp lib/parser/SchemaTreeBuilder.hpp lib/include/schema/Schema.hpp lib/include/julia_orm/Error.hpp lib/include/query/Query.hpp lib/include/query/Include.hpp lib/include/SQL/SqlQueryBuilder.hpp lib/SQL/SQLQueryBuilder.cpp lib/include/query/Select.hpp lib/include/julia_orm/DbContext.hpp lib/DbContext.cpp lib/parser/QueryBuilder.cpp lib/parser/QueryBuilder.hpp lib/include/schema/Interface.hpp lib/include/schema/TypeBlock.hpp lib/include/schema/TypeCall.hpp lib/include/schema/BasicType.hpp)
add_subdirectory(fmt EXCLUDE_FROM_ALL)

target_link_libraries(julia_orm fmt::fmt)