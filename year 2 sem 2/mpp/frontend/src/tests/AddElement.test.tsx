import React from 'react';
import { render, screen, fireEvent } from '@testing-library/react';
import AddElement from '../comps/AddElement';


describe('AddElement component', () => {
    test('renders Add Element title', () => {
        render(<AddElement onBackButtonClickHandle={() => {}} onSubmitClickHandle={() => {}} />);
        expect(screen.getByText('ADD ELEMENT')).toBeInTheDocument();
    });

    test('submitting the form with valid data', () => {
        const mockOnSubmitClickHandle = jest.fn();
        const mockOnBackButtonClickHandle = jest.fn();
        render(<AddElement onBackButtonClickHandle={mockOnBackButtonClickHandle} onSubmitClickHandle={mockOnSubmitClickHandle} />);

        const idInput = screen.getByLabelText('ID:');
        fireEvent.change(idInput, { target: { value: '1' } });

        const titleInput = screen.getByLabelText('TITLE:');
        fireEvent.change(titleInput, { target: { value: 'Test Title' } });

        const descInput = screen.getByLabelText('DESC:');
        fireEvent.change(descInput, { target: { value: 'Test Description' } });

        const gravityInput = screen.getByLabelText('GRAVITY:');
        fireEvent.change(gravityInput, { target: { value: '1' } });

        const submitButton = screen.getByText('ADD');
        fireEvent.click(submitButton);

        expect(mockOnSubmitClickHandle).toHaveBeenCalledWith({
            id: '1',
            title: 'Test Title',
            desc: 'Test Description',
            gravity: 1,
        });
    });
})

export {}

