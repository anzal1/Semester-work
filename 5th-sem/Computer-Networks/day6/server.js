const port = 3000;
const io = require("socket.io")(port);
console.log("Server started on port " + port);

io.of("/").on("connect", (socket) => {
  console.log("\nA client connected");

  socket.on("broadcast", (data) => {
    console.log("\n%s", data);
    socket.broadcast.emit("broadcast", data);
  });

  socket.emit("join", { sender: nickname, action: "join" });

  socket.on("join", (data) => {
    console.log("[INFO]: %s has joined the chat", data.sender);
  });

  socket.on("disconnect", (reason) => {
    console.log("\nA client disconnected, reason: %s", reason);
    console.log("Number of clients: %d", io.of("/").server.engine.clientsCount);
  });
});
