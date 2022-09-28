const io = require("socket.io-client");
const socket = io("http://localhost:3000");
const usersSocket = io("http://localhost:3000/users");
const ordersSocket = io("http://localhost:3000/orders");
var nickname = null;
var s_pattern = /^s;([A-Z0-9]+);(.+)/i;
var bg_pattern = /^bg;([A-Z0-9]+);(.+)/i;
console.log("Connecting to the server...");
socket.on("connect", () => {
  nickname = process.argv[2];
  console.log("[INFO]: Welcome %s", nickname);
  socket.emit("join", { sender: nickname, action: "join" });
});
socket.on("disconnect", (reason) => {
  console.log("[INFO]: Client disconnected, reason: %s", reason);
});

socket.on("join", (data) => {
  console.log("[INFO]: %s has joined the chat", data.sender);
});

const readline = require("readline");
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
rl.on("line", (input) => {
  if (true === input.startsWith("b;")) {
    var str = input.slice(2);
    socket.emit("broadcast", {
      sender: nickname,
      action: "broadcast",
      msg: str,
    });
  } else if ("ls;" === input) {
    socket.emit("list", { sender: nickname, action: "list" });
  } else if ("q;" === input) {
    socket.emit("quit", { sender: nickname, action: "quit" });
  } else if ("tr;" === input) {
    socket.emit("trace");
  } else if (true === s_pattern.test(input)) {
    var info = input.match(s_pattern);
    socket.emit("send", {
      sender: nickname,
      action: "send",
      receiver: info[1],
      msg: info[2],
    });
  } else if (true === input.startsWith("jg;")) {
    var str = input.slice(3);
    socket.emit("join_group", {
      sender: nickname,
      action: "join_group",
      group: str,
    });
  } else if (true === bg_pattern.test(input)) {
    var info = input.match(bg_pattern);
    socket.emit("broadcast_group", {
      sender: nickname,
      action: "broadcast_group",
      group: info[1],
      msg: info[2],
    });
  } else if (true === input.startsWith("mbr;")) {
    var str = input.slice(4);
    socket.emit("list_members_group", {
      sender: nickname,
      action: "list_members_group",
      group: str,
    });
  } else if (true === input.startsWith("msg;")) {
    var str = input.slice(4);
    socket.emit("list_messages_group", {
      sender: nickname,
      action: "list_messages_group",
      group: str,
    });
  } else if ("grp;" === input) {
    socket.emit("list_groups", { sender: nickname, action: "list_groups" });
  } else if (true === input.startsWith("lg;")) {
    var str = input.slice(3);
    socket.emit("leave_group", {
      sender: nickname,
      action: "leave_group",
      group: str,
    });
  }
});

socket.on("broadcast", (data) => {
  console.log("%s", data.msg);
});

socket.on("list", (data) => {
  console.log("[INFO]: List of nicknames:");
  for (var i = 0; i < data.users.length; i++) {
    console.log(data.users[i]);
  }
});

socket.on("send", (data) => {
  console.log("%s", data.msg);
});

socket.on("join_group", (data) => {
  console.log("[INFO]: %s has joined the group", data.sender);
});

socket.on("broadcast_group", (data) => {
  console.log("%s", data.msg);
});

socket.on("list_members_group", (data) => {
  console.log("[INFO]: List of members:");
  for (var i = data.members.length - 1; i >= 0; i--) {
    console.log(data.members[i]);
  }
});

socket.on("list_messages_group", (data) => {
  console.log("[INFO]: History of messages:");
  for (var i = data.msgs.length - 1; i >= 0; i--) {
    console.log(data.msgs[i]);
  }
});

socket.on("list_groups", (data) => {
  console.log("[INFO]: List of groups:");
  for (var i = data.groups.length - 1; i >= 0; i--) {
    console.log(data.groups[i]);
  }
});

socket.on("leave_group", (data) => {
  console.log("[INFO]: %s left the group", data.sender);
});
