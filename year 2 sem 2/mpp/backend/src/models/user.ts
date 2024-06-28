import { InferSchemaType, Schema, model } from "mongoose";

const userScheme = new Schema({
    username: {type: String, required: true, unique: true},
    email: {type: String, required: true, unique: true, select: false},
    password: {type: String, required: true, select: false},
})


type User = InferSchemaType<typeof userScheme>;
export default model<User>('User', userScheme);