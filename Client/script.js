function buildHeader(str) {
    return str + "TICTACTOE/1.0\r\n";
}

function buildValue(str, key, value) {
    return str + key + ": " + value + "\r\n";
}

function buildFooter(str) {
    return str + "\r\n\r\n";
}

console.log("n'importe quoi")

function setIdentityRequest(pseudo){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "setIdentity");
    response = buildValue(response, "Pseudo", pseudo);

    response = buildFooter(response);

    return response;

}

function getIdentityRequest(){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "getIdentity");

    response = buildFooter(response);

    return response;

}

//TODO createMatchRequest

function createMatchRequest(gridWidth, gridHeight, str_TODO, winSize){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "createMatch");
    response = buildValue(response, "GridWidth", gridWidth)
    response = buildValue(response, "GridHeight", gridHeight)
    response = buildValue(response, "PseudoPlayers", str_TODO);
    response = buildValue(response, "WinSize", winSize);

    response = buildFooter(response);

    return response;

}

function getMatchListRequest(){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "getMatchList");

    response = buildFooter(response);

    return response;

}

function getMatchInformationRequest(match_id){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "getMatchInformation");
    response = buildValue(response, "MatchID", match_id);

    response = buildFooter(response);

    return response;

}

function joinMatchRequest(match_id, mode){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "joinMatch");
    response = buildValue(response, "MatchID", match_id);
    response = buildValue(response, "Mode", mode);

    response = buildFooter(response);

    return response;

}

function playMatchRequest(match_id, coordinate_x, coordinate_y){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "playMatch");
    response = buildValue(response, "MatchID", match_id);
    response = buildValue(response, "CoordinateX", coordinate_x);
    response = buildValue(response, "CoordinateY", coordinate_y);

    response = buildFooter(response);

    return response;


}

function resetMatchRequest(match_id){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "resetMatch");
    response = buildValue(response, "MatchID", match_id);

    response = buildFooter(response);

    return response;

}

function quitMatchRequest(match_id){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "quitMatch");
    response = buildValue(response, "MatchID", match_id);

    response = buildFooter(response);

    return response;

}

function getPlayerInformationRequest(pseudo){

    response = "";

    response = buildHeader(response);

    response = buildValue(response, "Request", "getPlayerInformation");
    response = buildValue(response, "Pseudo", pseudo);

    response = buildFooter(response);

    return response;

}

function getLineParsing(buffer) {

    var delimiter_position = buffer.indexOf("\r\n");

    return [buffer.substring(0, delimiter_position+2), buffer.substr(delimiter_position+2)];

}


function headerParsing(line) {

    return line == "TICTACTOE/1.0\r\n";

}

function footerParsing(line) {

    return (line == "\r\n");

}

function valueParsing(line) {

    var delimiter_position = line.indexOf(": ");

    var key = line.substring(0, delimiter_position);

    var value = line.substr(delimiter_position+2);
    value =  value.substring(0, value.length-2);

    return [key, value];

}

function getIdentityResponseParsing(buffer) {

    var parseData = getLineParsing(buffer);
    var line = parseData[0]; buffer = parseData[1];

    if(headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0]; buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if(lineParsing[0] == "Response" && lineParsing[1] == "getIdentity") {

            parseData = getLineParsing(buffer);
            line = parseData[0]; buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "Pseudo"){

                var pseudo = lineParsing[1]

                var parseData = getLineParsing(buffer);
                line = parseData[0]; buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "2-0") {

                    var errorcode = lineParsing[1]

                    var parseData = getLineParsing(buffer);
                    line = parseData[0]; buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (footerParsing(line)) {

                        //pseudo
                        //Error Code

                        return true;

                    }

                }

            }
        }

    }

    return false;
}

function setIdentityResponseParsing(buffer) {

    var parseData = getLineParsing(buffer);
    var line = parseData[0]; buffer = parseData[1];

    if(headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0]; buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if(lineParsing[0] == "Response" && lineParsing[1] == "setIdentity") {

            parseData = getLineParsing(buffer);
            line = parseData[0]; buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "Pseudo"){

                var pseudo = lineParsing[1]

                var parseData = getLineParsing(buffer);
                line = parseData[0]; buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "1-0") {

                    var errorcode = lineParsing[1]

                    var parseData = getLineParsing(buffer);
                    line = parseData[0]; buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (footerParsing(line)) {

                        //pseudo
                        //Error Code

                        return true;

                    }

                }

            }
        }

    }

    return false;
}

function createMatchResponseParsing(buffer) {

    var parseData = getLineParsing(buffer);
    var line = parseData[0]; buffer = parseData[1];

    if(headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0]; buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if(lineParsing[0] == "Response" && lineParsing[1] == "createMatch") {

            parseData = getLineParsing(buffer);
            line = parseData[0]; buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "MatchId"){

                var match_id = lineParsing[1]

                var parseData = getLineParsing(buffer);
                line = parseData[0]; buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "GridWidth") {

                    var grid_width = lineParsing[1]

                    var parseData = getLineParsing(buffer);
                    line = parseData[0]; buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (lineParsing[0] == "GridHeight") {

                        var grid_height = lineParsing[1]

                        var parseData = getLineParsing(buffer);
                        line = parseData[0];
                        buffer = parseData[1];

                        var lineParsing = valueParsing(line);

                        if (lineParsing[0] == "PseudoPlayers") {

                            var players = lineParsing[1]

                            var parseData = getLineParsing(buffer);
                            line = parseData[0];
                            buffer = parseData[1];

                            var lineParsing = valueParsing(line);

                            if (lineParsing[0] == "WinSize") {

                                var winsize = lineParsing[1]

                                var parseData = getLineParsing(buffer);
                                line = parseData[0];
                                buffer = parseData[1];

                                var lineParsing = valueParsing(line);

                                if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "3-0") {

                                    var errorcode = lineParsing[1]

                                    var parseData = getLineParsing(buffer);
                                    line = parseData[0];
                                    buffer = parseData[1];

                                    var lineParsing = valueParsing(line);

                                    if (footerParsing(line)) {

                                        //match_id
                                        //grid_width
                                        //grid_height
                                        //players
                                        //winsize
                                        //Error Code

                                        return true;

                                    }

                                }

                            }

                        }

                    }

                }

            }
        }

    }

    return false;
}

function getMatchListResponseParsing(buffer){

    var parseData = getLineParsing(buffer);
    var line = parseData[0]; buffer = parseData[1];

    if(headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0]; buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if(lineParsing[0] == "Response" && lineParsing[1] == "getMatchList") {

            parseData = getLineParsing(buffer);
            line = parseData[0]; buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "MatchCount"){

                var match_count = lineParsing[1]

                var parseData = getLineParsing(buffer);
                line = parseData[0]; buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "MatchList") {

                    var match_list = lineParsing[1]

                    var parseData = getLineParsing(buffer);
                    line = parseData[0];
                    buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "4-0") {

                        var errorcode = lineParsing[1]

                        var parseData = getLineParsing(buffer);
                        line = parseData[0];
                        buffer = parseData[1];

                        var lineParsing = valueParsing(line);

                        if (footerParsing(line)) {

                            //match_count
                            //match_list
                            //Error Code

                            return true;

                        }

                    }

                }

            }
        }

    }

    return false;

}

function getMatchInformationResponseParsing(buffer)
{

    var parseData = getLineParsing(buffer);
    var line = parseData[0];
    buffer = parseData[1];

    if (headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0];
        buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if (lineParsing[0] == "Response" && lineParsing[1] == "getMatchInformation") {

            parseData = getLineParsing(buffer);
            line = parseData[0];
            buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "MatchId") {

                var match_id = lineParsing[1];

                var parseData = getLineParsing(buffer);
                line = parseData[0];
                buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "DoYouPlay") {

                    var do_you_play = lineParsing[1];

                    var parseData = getLineParsing(buffer);
                    line = parseData[0];
                    buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (lineParsing[0] == "CanYouJoin") {

                        var can_you_play = lineParsing[1];

                        var parseData = getLineParsing(buffer);
                        line = parseData[0];
                        buffer = parseData[1];

                        var lineParsing = valueParsing(line);

                        if (lineParsing[0] == "Grid") {

                            var grid = lineParsing[1];

                            var parseData = getLineParsing(buffer);
                            line = parseData[0];
                            buffer = parseData[1];

                            var lineParsing = valueParsing(line);

                            if (lineParsing[0] == "GridWidth") {

                                var grid_width = lineParsing[1];

                                var parseData = getLineParsing(buffer);
                                line = parseData[0];
                                buffer = parseData[1];

                                var lineParsing = valueParsing(line);

                                if (lineParsing[0] == "GridHeight") {

                                    var grid_height = lineParsing[1];

                                    var parseData = getLineParsing(buffer);
                                    line = parseData[0];
                                    buffer = parseData[1];

                                    var lineParsing = valueParsing(line);

                                    if (lineParsing[0] == "Players") {

                                        var players = lineParsing[1];

                                        var parseData = getLineParsing(buffer);
                                        line = parseData[0];
                                        buffer = parseData[1];

                                        var lineParsing = valueParsing(line);

                                        if (lineParsing[0] == "State") {

                                            var state = lineParsing[1];

                                            var parseData = getLineParsing(buffer);
                                            line = parseData[0];
                                            buffer = parseData[1];

                                            var lineParsing = valueParsing(line);

                                            if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "5-0") {

                                                var errorcode = lineParsing[1];

                                                var parseData = getLineParsing(buffer);
                                                line = parseData[0];
                                                buffer = parseData[1];

                                                var lineParsing = valueParsing(line);

                                                if (footerParsing(line)) {

                                                    //match_id
                                                    //do_you_play
                                                    //can_you_play
                                                    //grid
                                                    //grid_width
                                                    //grid_height
                                                    //players
                                                    //state
                                                    //Error Code

                                                    return true;

                                                }

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;

}

function joinMatchResponseParsing(buffer)
{

    var parseData = getLineParsing(buffer);
    var line = parseData[0];
    buffer = parseData[1];

    if (headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0];
        buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if (lineParsing[0] == "Response" && lineParsing[1] == "joinMatch") {

            parseData = getLineParsing(buffer);
            line = parseData[0];
            buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "MatchId") {

                var match_id = lineParsing[1];

                var parseData = getLineParsing(buffer);
                line = parseData[0];
                buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "Mode") {

                    var mode = lineParsing[1];

                    var parseData = getLineParsing(buffer);
                    line = parseData[0];
                    buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "6-0") {

                        var errorcode = lineParsing[1];

                        var parseData = getLineParsing(buffer);
                        line = parseData[0];
                        buffer = parseData[1];

                        var lineParsing = valueParsing(line);

                        if (footerParsing(line)) {

                            //match_id
                            //mode
                            //Error Code

                            return true;

                        }

                    }
                }
            }
        }
    }

    return false;

}

function playMatchResponseParsing(buffer)
{

    var parseData = getLineParsing(buffer);
    var line = parseData[0];
    buffer = parseData[1];

    if (headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0];
        buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if (lineParsing[0] == "Response" && lineParsing[1] == "playMatch") {

            parseData = getLineParsing(buffer);
            line = parseData[0];
            buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "MatchId") {

                var match_id = lineParsing[1];

                var parseData = getLineParsing(buffer);
                line = parseData[0];
                buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "Grid") {

                    var grid = lineParsing[1];

                    var parseData = getLineParsing(buffer);
                    line = parseData[0];
                    buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (lineParsing[0] == "Players") {

                        var players = lineParsing[1];

                        var parseData = getLineParsing(buffer);
                        line = parseData[0];
                        buffer = parseData[1];

                        var lineParsing = valueParsing(line);

                        if (lineParsing[0] == "Result") {

                            var result = lineParsing[1];

                            var parseData = getLineParsing(buffer);
                            line = parseData[0];
                            buffer = parseData[1];

                            var lineParsing = valueParsing(line);

                            if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "7-0") {

                                var errorcode = lineParsing[1];

                                var parseData = getLineParsing(buffer);
                                line = parseData[0];
                                buffer = parseData[1];

                                var lineParsing = valueParsing(line);

                                if (footerParsing(line)) {

                                    //match_id
                                    //grid
                                    //players
                                    //result
                                    //Error Code

                                    return true;

                                }

                            }
                        }
                    }
                }
            }
        }
    }

    return false;

}

function resetMatchResponseParsing(buffer)
{

    var parseData = getLineParsing(buffer);
    var line = parseData[0];
    buffer = parseData[1];

    if (headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0];
        buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if (lineParsing[0] == "Response" && lineParsing[1] == "resetMatch") {

            parseData = getLineParsing(buffer);
            line = parseData[0];
            buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "MatchId") {

                var match_id = lineParsing[1];

                var parseData = getLineParsing(buffer);
                line = parseData[0];
                buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "8-0") {

                    var errorcode = lineParsing[1];

                    var parseData = getLineParsing(buffer);
                    line = parseData[0];
                    buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (footerParsing(line)) {

                        //match_id

                        //Error Code

                        return true;

                    }

                }
            }
        }
    }

    return false;

}

function quitMatchResponseParsing(buffer)
{

    var parseData = getLineParsing(buffer);
    var line = parseData[0];
    buffer = parseData[1];

    if (headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0];
        buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if (lineParsing[0] == "Response" && lineParsing[1] == "quitMatch") {

            parseData = getLineParsing(buffer);
            line = parseData[0];
            buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "MatchId") {

                var match_id = lineParsing[1];

                var parseData = getLineParsing(buffer);
                line = parseData[0];
                buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "9-0") {

                    var errorcode = lineParsing[1];

                    var parseData = getLineParsing(buffer);
                    line = parseData[0];
                    buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (footerParsing(line)) {

                        //match_id
                        //Error Code

                        return true;

                    }

                }
            }
        }
    }

    return false;

}

function getPlayerInformationResponseParsing(buffer)
{

    var parseData = getLineParsing(buffer);
    var line = parseData[0];
    buffer = parseData[1];

    if (headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0];
        buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if (lineParsing[0] == "Response" && lineParsing[1] == "getPlayerInformation") {

            parseData = getLineParsing(buffer);
            line = parseData[0];
            buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "Pseudo") {

                var pseudo = lineParsing[1];

                var parseData = getLineParsing(buffer);
                line = parseData[0];
                buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (lineParsing[0] == "GlobalScore") {

                    var global_score = lineParsing[1];

                    var parseData = getLineParsing(buffer);
                    line = parseData[0];
                    buffer = parseData[1];

                    var lineParsing = valueParsing(line);

                    if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "10-0") {

                        var errorcode = lineParsing[1];

                        var parseData = getLineParsing(buffer);
                        line = parseData[0];
                        buffer = parseData[1];

                        var lineParsing = valueParsing(line);

                        if (footerParsing(line)) {

                            //pseudo
                            //global_score
                            //Error Code

                            return true;

                        }

                    }
                }
            }
        }
    }

    return false;

}

function genericErrorResponseParsing(buffer)
{

    var parseData = getLineParsing(buffer);
    var line = parseData[0];
    buffer = parseData[1];

    if (headerParsing(line)) {

        var parseData = getLineParsing(buffer);
        line = parseData[0];
        buffer = parseData[1];

        var lineParsing = valueParsing(line);

        if (lineParsing[0] == "Response" && lineParsing[1] == "genericError") {

            parseData = getLineParsing(buffer);
            line = parseData[0];
            buffer = parseData[1];

            var lineParsing = valueParsing(line);

            if (lineParsing[0] == "ErrorCode" && lineParsing[1] == "-1") {

                var errorcode = lineParsing[1];

                var parseData = getLineParsing(buffer);
                line = parseData[0];
                buffer = parseData[1];

                var lineParsing = valueParsing(line);

                if (footerParsing(line)) {

                    //Error Code

                    return true;

                }

            }
        }
    }

    return false;

}

console.log(getPlayerInformationRequest("Jack"));



console.log(genericErrorResponseParsing("TICTACTOE/1.0\r\nResponse: genericError\r\nErrorCode: -1\r\n\r\n\r\n"))
