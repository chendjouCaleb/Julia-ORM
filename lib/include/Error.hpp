//
// Created by HP on 20/12/2022.
//

#ifndef JULIA_ORM_ERROR_HPP
#define JULIA_ORM_ERROR_HPP

enum ErrorType {
    ERR_TYPE_SYNTAX,
    ERR_TYPE_QUERY,
    ERR_TYPE_SCHEMA
};

enum SyntaxErrorCode {
    SYNTAX_ERR_UNEXPECTED_CHAR = 0,
    SYNTAX_ERR_UNEXPECTED_TOKEN = 1,
};

enum QueryErrorCode {
    QUERY_ERR_UNEXPECTED_CHAR = 0,
    QUERY_ERR_UNEXPECTED_TOKEN = 1,
};

enum SchemaErrorCode {
    SCHEMA_ERR_UNKNOWN_DB_SET = 1,
};

class Error {
    ErrorType type;
    SchemaErrorCode code;
    QueryErrorCode queryErrorCode;
    SyntaxErrorCode syntaxErrorCode;
    std::string message;
};


#endif //JULIA_ORM_ERROR_HPP
