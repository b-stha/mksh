#pragma once
#include <string>

namespace mksh {
    enum class TokenType {
        PIPE,
        OR,
        BACKGROUND,
        AND,
        REDIRECT_IN,
        HEREDOC,
        HERESTRING,
        REDIRECT_OUT,
        REDIRECT_APPEND,
        CLOBBER,
        LPAREN,
        RPAREN,
        SEMICOLON,
        WORD
    };

    struct Token {
        TokenType type;
        std::string value;
    };
}