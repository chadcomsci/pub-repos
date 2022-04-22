import mysql from 'mysql'; 
import express from 'express';
import WebSocket, { WebSocketServer } from 'ws';

const HTTP_PORT = 8080;
const SOCK_PORT = 9090;

const app = express();
const wss = new WebSocketServer({ port: SOCK_PORT });

var db;
var client_ips = [];

function bind_sock(){
  // client connects
  wss.on('connection', function connection(ws, req){
    console.log('IP '+req.socket.remoteAddress+' connected.');
    client_ips.push({ 'ws': ws, 'ip': req.socket.remoteAddress});
    // message rec from client
    ws.on('message', function incoming(message){
      console.log('received: %s', message);
    });
  });
}

function init_server(){
	app.listen(HTTP_PORT, function(){
	  console.log(`Example app listening at http://localhost:${HTTP_PORT}`)
	});
}

function init_db(){
	db = mysql.createConnection({
         host: "localhost",
         user: "pi",
         password: "somepassword"
     });
}

function ws_send(ws, msg){
  if(ws.readyState === WebSocket.OPEN){
    ws.send(msg);
  }
}

function bind_routes(){
	app.use(express.static('static_pages'));

	app.get('/', function(req, res){
	  console.log('Request received from '+req.ip);
	  res.send('{"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}');
	});

	app.get('/test', function(req, res){
	  res.send(stitch('Hello World! 8'));
	});

  app.get('/blinker_led', function(req, res){
    // wss.clients[0].send('test blinker');
    // client_ips[client_ips.length-1].ws.send();
    ws_send(client_ips[client_ips.length-1].ws, '{"msg": "some JSON obj","val": 999}');

    console.log('blinker_led accessed.');
    res.send('something to close');
  });

  app.get('/on_led', function(req, res){
    ws_send(client_ips[client_ips.length-1].ws, 'ON_LED_1');
    res.send('');
  });

  app.get('/off_led', function(req, res){
    ws_send(client_ips[client_ips.length-1].ws, 'OFF_LED_1');
    res.send('');
  });

}

function stitch(response){
	var basic_content_start = `<html><body>`;
	var basic_content_end = `</body></html>`;
	return basic_content_start+response+basic_content_end;
}

init_server();
bind_routes();
init_db();
bind_sock();






