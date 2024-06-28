import "dotenv/config";
import express, {NextFunction, Request} from "express";
import e from "express";
import elementsRoutes from "./routes/elements";
import childrenRoutes from "./routes/children";
import morgan from "morgan";
import createHttpError, { isHttpError } from "http-errors";
import userRoutes from "./routes/users";

import ElementChildModel from "./models/elementChild";
import session from "express-session";
import env from "./util/validateEnv"
import MongoStore from "connect-mongo";
import cors from 'cors';



const app = express();
app.use(cors());

app.use(morgan("dev"));
app.use(express.json())

app.use(session({
  secret: env.SESSION_SECRET,
  resave: false,
  saveUninitialized: false,
  cookie: {
    maxAge: 60*60*24*1000,
  },
  rolling: true,
  store: MongoStore.create({
    mongoUrl: env.MONGO_CONNECTION_STRING
  }),
}))

app.use("/api/users", userRoutes);
app.use("/api/elements", elementsRoutes);
app.use("/api/children", childrenRoutes);

// app.get("/", async (_req, res, next) => {
//   try {
//     const elements = await ElementChildModel.find().exec();
//     res.status(200).json(elements);
//   } catch (error) {
//     next(error);
//   }
// });


app.use((req, res, next) => {
  next(createHttpError(404, "Endpoint not found"));
});

// eslint-disable-next-line @typescript-eslint/no-unused-vars
app.use((error: Error, _req: Request, res: e.Response, _next: NextFunction) => {
  console.error(error);
  let errorMessage = "Error unknown";
  let statusCode = 500;
  if(isHttpError(error)) {
    statusCode = error.status;
    errorMessage = error.message;
  }
  res.status(statusCode).json({ error: errorMessage });
});

export default    app;

