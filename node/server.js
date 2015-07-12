http = require('http');
fs = require('fs');
server = http.createServer( function(req, res) {

//    console.dir(req.param);

    if (req.method == 'PUT') {
        console.log("PUT");
        var body = '';
        console.log(req.headers);
        req.on('data', function (data) {
            body += data;
            console.log("body: " + body);
        });
        req.on('end', function () {
            console.log("done");
        });
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.end('post received');
    }
    else
    {
        console.log("GET");
        var html = '<html><body><form method="post" action="http://localhost:1337">Name: <input type="text" name="name" /><input type="submit" value="Submit" /></form></body>';
        //var html = fs.readFileSync('index.html');
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.end(html);
    }

});

port = 80;
host = '0.0.0.0';
server.listen(port, host);
console.log('Listening at http://' + host + ':' + port);
