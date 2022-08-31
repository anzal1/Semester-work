const cors = require("cors");
const express = require("express");
const http = require("http");
const socketIo = require("socket.io");

const port = process.env.PORT || 5001;
const index = require("./routes/index");

const app = express();

const server = http.createServer(app);

const io = socketIo(server); // < Interesting!
const corsOption = {
  origin: ["http://localhost:3000"],
};

let interval;

io.on("connection", (socket) => {
  console.log("New client connected");
  if (interval) {
    clearInterval(interval);
  }
  interval = setInterval(() => getApiAndEmit(socket), 1000);
  socket.on("disconnect", () => {
    console.log("Client disconnected");
    clearInterval(interval);
  });
});
app.use(index);
app.use(cors({ origin: corsOption, optionsSuccessStatus: 200 }));

const getApiAndEmit = (socket) => {
  const response = new Date();
  console.log("Emitting");
  // Emitting a new message. Will be consumed by the client
  socket.emit("FromAPI", response);
};

server.listen(port, () => console.log(`Listening on port ${port}`));
