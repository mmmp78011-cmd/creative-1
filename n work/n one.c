
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_html_header() {
    printf("Content-Type: text/html\r\n\r\n");
}

void print_styled_html_start() {
    printf("<!DOCTYPE html>\n"
           "<html lang=\"en\">\n"
           "<head>\n"
           "    <meta charset=\"UTF-8\">\n"
           "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
           "    <title>Quiz Result</title>\n"
           "    <style>\n"
           "        body {\n"
           "            font-family: 'Segoe UI', Arial, sans-serif;\n"
           "            background-color: #f0f2f5;\n"
           "            margin: 0;\n"
           "            padding: 20px;\n"
           "            display: flex;\n"
           "            justify-content: center;\n"
           "            align-items: center;\n"
           "            min-height: 100vh;\n"
           "        }\n"
           "        .result-container {\n"
           "            background: white;\n"
           "            padding: 2rem;\n"
           "            border-radius: 10px;\n"
           "            box-shadow: 0 2px 10px rgba(0,0,0,0.1);\n"
           "            max-width: 400px;\n"
           "            width: 100%%;\n"
           "            text-align: center;\n"
           "        }\n"
           "        h1 {\n"
           "            color: #1a73e8;\n"
           "            margin-bottom: 1.5rem;\n"
           "        }\n"
           "        .message {\n"
           "            font-size: 1.2rem;\n"
           "            padding: 1rem;\n"
           "            border-radius: 5px;\n"
           "            margin: 1rem 0;\n"
           "        }\n"
           "        .success {\n"
           "            background-color: #e6f4ea;\n"
           "            color: #137333;\n"
           "        }\n"
           "        .error {\n"
           "            background-color: #fce8e6;\n"
           "            color: #c5221f;\n"
           "        }\n"
           "        .button {\n"
           "            background-color: #1a73e8;\n"
           "            color: white;\n"
           "            border: none;\n"
           "            padding: 0.8rem 1.5rem;\n"
           "            border-radius: 5px;\n"
           "            font-size: 1.1rem;\n"
           "            text-decoration: none;\n"
           "            display: inline-block;\n"
           "            margin-top: 1rem;\n"
           "            transition: background-color 0.3s;\n"
           "        }\n"
           "        .button:hover {\n"
           "            background-color: #1557b0;\n"
           "        }\n"
           "    </style>\n"
           "</head>\n"
           "<body>\n"
           "    <div class=\"result-container\">\n");
}

void print_html_end() {
    printf("        <a href=\"/n%%20one.html\" class=\"button\">Try Again</a>\n"
           "    </div>\n"
           "</body>\n"
           "</html>\n");
}

int main(void) {
    char *method = getenv("REQUEST_METHOD");
    char *content_length_str = getenv("CONTENT_LENGTH");
    char input[1024] = {0};
    int answer = 0;
    
    // Read POST data
    if (method && strcmp(method, "POST") == 0 && content_length_str) {
        int content_length = atoi(content_length_str);
        if (content_length > 0 && content_length < sizeof(input)) {
            fread(input, 1, content_length, stdin);
            
            // Parse answer=X from POST data
            char *answer_str = strstr(input, "answer=");
            if (answer_str) {
                answer = atoi(answer_str + 7);  // Skip "answer="
            }
        }
    }
    
    send_html_header();
    print_styled_html_start();
    
    printf("        <h1>Quiz Result</h1>\n");
    
    if (answer == 14) {
        printf("        <div class=\"message success\">\n"
               "            <strong>Correct!</strong> 7 + 7 = 14\n"
               "        </div>\n");
    } else {
        printf("        <div class=\"message error\">\n"
               "            Try again! Your answer %d is incorrect.\n"
               "        </div>\n", answer);
    }
    
    print_html_end();
    return 0;
}
