import React from 'react';
 import {render, screen, fireEvent, getAllByTestId} from '@testing-library/react';
import Home from '../comps/Home'; // Update the path
import { PageEnum } from '../comps/Element.type'
// import {sortDecreaseGamesByTitle, sortIncreaseGamesByTitle} from "../components/Service"; // Make sure to import PageEnum
import { ResizeObserver } from '@juggle/resize-observer';
import 'use-resize-observer';
// const ResizeObserverMock = jest.fn(() => ({
//     observe: jest.fn(),
//     unobserve: jest.fn(),
//     disconnect: jest.fn(),
//   }));
  
//   // Stub the global ResizeObserver
//   jest.setMock('ResizeObserver', ResizeObserverMock);


describe('Home component', () => {
    
    test('renders list and buttons', () => {
        render(<Home/>);
        const addButton = screen.getByText('ADD ELEMENT');
        expect(addButton).toBeInTheDocument();
    });

    test('adds element', () => {
        render(<Home/>);
        const addButton = screen.getByText('ADD ELEMENT');
        fireEvent.click(addButton);
        const submitButton = screen.getByText('ADD');
        expect(submitButton).toBeInTheDocument();
    });

    test('back button works', () => {
        render(<Home/>);
        const addButton = screen.getByText('ADD ELEMENT');
        fireEvent.click(addButton);
        const backButton = screen.getByText('BACK');
        fireEvent.click(backButton);
        const addButtonAfterNavigate = screen.getByText('ADD ELEMENT');
        expect(addButtonAfterNavigate).toBeInTheDocument();
    });
    test('pagination works', () => {
        render(<Home/>);
        const selectRecordsPerPage = screen.getByTestId('records-per-page');
        fireEvent.change(selectRecordsPerPage, { target: { value: '5' } });
        const table = screen.getByRole('table'); // get the table element
        // eslint-disable-next-line testing-library/no-node-access
        const tableRows = table.querySelectorAll('tr'); // query for all <tr>s
        expect(tableRows.length).toBe(4); // 3 rows + 1 header row
    });

const mockData = [{
        id: '1',
            title: 'Test Title',
            desc: 'Test Description',
            gravity: 1,

},{
    id: '2',
    title: 'AA Test Title',
    desc: 'Test Description',
    gravity: 55,
},
{
    id: '3',
    title: 'ZZ Test Title',
    desc: 'Test Description',
    gravity: 22,
}];

    test('sorts elements alphabetically', () => {
        render(<Home/>);
        
        fireEvent.click(screen.getByText('ADD ELEMENT'));
        const idInput = screen.getByLabelText('ID:');
        fireEvent.change(idInput, { target: { value: '1' } });

        const titleInput = screen.getByLabelText('TITLE:');
        fireEvent.change(titleInput, { target: { value: 'ZZZ Test Title' } });

        const descInput = screen.getByLabelText('DESC:');
        fireEvent.change(descInput, { target: { value: 'Test Description' } });

        const gravityInput = screen.getByLabelText('GRAVITY:');
        fireEvent.change(gravityInput, { target: { value: '1' } });

        const submitButton = screen.getByText('ADD');
        fireEvent.click(submitButton);

        const selectSortOptions = screen.getByTestId('sort-options');
        fireEvent.change(selectSortOptions, { target: { value: 'alphabetically-decrease' } });
        const table = screen.getByRole('table'); // get the table element
        const tableRows1 = table.querySelectorAll('tr'); // query for all <tr>s
        
        // delete the item with title 'TITLE'
        const tableRows2 = Array.from(tableRows1).filter(row => row.children[1].textContent !== 'TITLE');
        const titles = Array.from(tableRows2).map(row => row.children[1].textContent); // get the title from the second <td>
        expect(titles).toEqual(['ZZZ Test Title', 'Title 3', 'Title 2', 'Title 1']);
    });

});

export {}