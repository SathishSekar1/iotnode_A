var http = require('http');

var fs = require('fs');

// Include the public functions from 'helpers.js'
var helpers = require('./helpers');

var databaseSurname = ' Heisenberg';



function handle_incoming_request (req, res) 
{
    console.log("INCOMING REQUEST: " + req.method + " " + req.url);
    load_sensor_data(function(err, readings)
	{ 
	    if(err){console.log("Couldn't read file");}
	    console.log(readings);
	    //readings = helpers.concatenateNames(readings, databaseSurname);
	    var valuestring = readings.split(",");
            var myJSON = { "Temperature":valuestring[0],"Humidity":valuestring[1],"Wind Speed":valuestring[2],"Time":valuestring[3],"Loation":valuestring[4] };
	    console.log(myJSON.Temperature);
	    res.writeHead(200, { "Content-Type" : "application/json" });
	    res.end(JSON.stringify(myJSON));
   	});
}



function load_sensor_data(callback) 
{
   fs.readFile("sensorlog.txt",'utf8', function (err, readings){ if(err){callback(err);return;} callback(null, readings); });
}

var s = http.createServer(handle_incoming_request);

s.listen(8080);