import { IElement } from "./Element.type";

interface FeaturesProps {
    elementList: IElement[];
}

export const sortAscByTitle = ({elementList}: FeaturesProps): IElement[] => {
    return [...elementList].sort((a, b) => a.title.localeCompare(b.title));
}

export const sortDescByTitle = ({elementList}: FeaturesProps): IElement[] => {
    return [...elementList].sort((a, b) => b.title.localeCompare(a.title));
}

export const sortAscByGravity = ({elementList}: FeaturesProps): IElement[] => {
    return [...elementList].sort((a,b) => a.gravity - b.gravity);
}

export const sortDescByGravity = ({elementList}: FeaturesProps): IElement[] => {
    return [...elementList].sort((a,b) => b.gravity - a.gravity);
}