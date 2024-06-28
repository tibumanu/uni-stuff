import { randomInt } from "crypto";
import React from "react";

export interface IElement{
    id: string;
    title: string;
    desc: string;
    gravity: number;
    children?: ISubElement[];
}

export interface ISubElement {
    id: string;
    desc: string;
    rating: number;
}

export const dummyElementList : IElement[] = [{
    id: new Date().getTime().toString() +  Math.ceil((Math.random()*10)**2), // so IDs aren't the same - adds a small-ish number to the end
    title: "Title 1",
    desc: "Description 1",
    gravity: 1
},
{
    id: new Date().getTime().toString() +  Math.ceil((Math.random()*10)**2),
    title: "Title 2",
    desc: "Description 2",
    gravity: 5
},
{
    id: new Date().getTime().toString()+  Math.ceil((Math.random()*10)**2),
    title: "Title 3",
    desc: "Description 3",
    gravity: 12
}];

export{};

export enum PageEnum{
    list,
    add,
    edit
}