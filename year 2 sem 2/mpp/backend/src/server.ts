import app from "./app";
import mongoose from "mongoose";
import env from "./util/validateEnv" /// <reference path="../util/validateEnv.d.ts" />;


const port = env.PORT;

if(!port) {
  console.error("bad port or not defined in .env file");
  process.exit(1);
}

mongoose.connect(env.MONGO_CONNECTION_STRING!)
.then(() => {
    console.log("Mongoose connected, connected to MongoDB");
    app.listen(port!, () => {
      console.log(`Server is running on port ${port}`);
    });
}).catch(console.error);

