import React from 'react';
import { render, screen, fireEvent } from '@testing-library/react';
import ElementList  from '../comps/ElementList';
import EditElement from '../comps/EditElement';

describe('EditElement component', () => {
    test('renders Edit Element form', () => {
        render(<EditElement onBackButtonClickHandle={() => {}} onSubmitClickHandle={() => {}} onUpdateClickHandle={() =>{}}/>);
        expect(screen.getByText('EDIT ELEMENT')).toBeInTheDocument();
    });
    test('updates element on submit', () => {
        const elements = [{ id: 1, name: 'Hydrogen', gravity: 1 }];
        const onUpdateClickHandle = jest.fn();
        render(<EditElement onBackButtonClickHandle={() => {}} onSubmitClickHandle={() => {}} onUpdateClickHandle={onUpdateClickHandle} elements={elements} />);
        fireEvent.change(screen.getByLabelText('TITLE:'), { target: { value: 'Title TEST' } });
        fireEvent.change(screen.getByLabelText('GRAVITY:'), { target: { value: 10 } });
        fireEvent.click(screen.getByText('UPDATE'));
        expect(onUpdateClickHandle).toHaveBeenCalledWith({ id: "", title: 'Title TEST', gravity: "10", desc:"" });
    });
});