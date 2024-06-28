import { InferSchemaType, Schema, model } from 'mongoose';
const elementSchema = new Schema({
    title: { type: String, required: true },
    desc: { type: String, required: false },
    gravity: { type: Number, required: true }}, { timestamps: true}
);

type Element = InferSchemaType<typeof elementSchema>;

export default model<Element>('Element', elementSchema);