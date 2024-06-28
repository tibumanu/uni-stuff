import {ideas} from '../models/ideas';

export function getAllIdeas(){
    return ideas;
}

export function getFromServer(){
    return fetch('http://localhost:5000/api/elements')
    .then(response => response.json())
    .then(data => data);
}

export function deleteIdea(title: string){
    const index = ideas.findIndex(idea => idea.title === title);
    if(index === -1){
        throw new Error("Idea not found");
        return false;
    }else{
    ideas.splice(index, 1);
    return true;
    }
}

export function addIdea(title: string, desc: string, gravity: number){
    const newIdea = {title, desc, gravity};
    ideas.push(newIdea);
    return newIdea;
}

export function updateIdea(title: string, desc: string, gravity: number){
    const index = ideas.findIndex(idea => idea.title === title);
    if(index === -1){
        throw new Error("Idea not found");
    }
    ideas[index] = {title, desc, gravity};
    return ideas[index];
}

export function getIdea(title: string){
    return ideas.find(idea => idea.title === title);
}

export function getSortedIdeas(){
    return ideas.sort((a, b) => b.gravity - a.gravity);
}

export function getFilteredIdeas(smth: string){
    return ideas.filter(idea => idea.title.includes(smth) || idea.desc.includes(smth));
}

export async function getGamesByPage(currentPage: number, recordsPerPage: number) {
    const indexOfLastRecord = currentPage * recordsPerPage;
    const indexOfFirstRecord = indexOfLastRecord - recordsPerPage;
    const records = await getFromServer()
    const currentRecords = records.slice(indexOfFirstRecord, indexOfLastRecord);
    const totalPages = Math.ceil(records.length / recordsPerPage);

    return { currentRecords, totalPages};
}