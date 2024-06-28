import { InferSchemaType, Schema, model } from "mongoose";
import {Types} from "mongoose";
const elementChildSchema = new Schema({
    parentID: { type: Types.ObjectId, required: true },
    desc: { type: String, required: false },
    rating: { type: Number, required: true }
}, { timestamps: true });

type ElementChild = InferSchemaType<typeof elementChildSchema>;

export default model<ElementChild>("ElementChild", elementChildSchema);

