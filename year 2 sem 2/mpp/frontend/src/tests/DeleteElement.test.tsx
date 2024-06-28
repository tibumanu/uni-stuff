import React from 'react';
import { render, screen, fireEvent } from '@testing-library/react';
import ElementList  from '../comps/ElementList';
import onDeleteClickHandle from '../comps/ElementList';

describe('DeleteElement component', () => {
    test('renders properly', () => {
        render(<ElementList onDeleteClickHandle={() => { } } onEdit={() => { } } list={[]} />);
        expect(screen.getByText('ID')).toBeInTheDocument();
        expect(screen.getByText('TITLE')).toBeInTheDocument();
        expect(screen.getByText('DESCRIPTION')).toBeInTheDocument();
        expect(screen.getByText('GRAVITY')).toBeInTheDocument();
        expect(screen.getByText('Action')).toBeInTheDocument();
    });
    test('clicks properly', () => {
        const mockOnDeleteClickHandle = jest.fn();
        const mockOnEdit = jest.fn();
        render(<ElementList onDeleteClickHandle={mockOnDeleteClickHandle} onEdit={mockOnEdit} list={[{
            id: '1',
            title: 'Test Title',
            desc: 'Test Description',
            gravity: 1,
        }]} />);
        const deleteButton = screen.getByText('Delete');
        fireEvent.click(deleteButton);
        expect(mockOnDeleteClickHandle).toHaveBeenCalled();
    });

})
