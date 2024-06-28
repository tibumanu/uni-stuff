import React from 'react';
import { render, screen } from '@testing-library/react';
import BarChart from '../comps/BarChart';
import { ResizeObserver } from '@juggle/resize-observer';


const anyGlobal = global as any;

// const ResizeObserverMock = jest.fn(() => ({
//   observe: jest.fn(),
//   unobserve: jest.fn(),
//   disconnect: jest.fn(),
// }));

// // Stub the global ResizeObserver
// jest.setMock('ResizeObserver', ResizeObserverMock);

const mockIntersectionObserver = jest.fn();
mockIntersectionObserver.mockReturnValue({
  observe: () => null,
  unobserve: () => null,
  disconnect: () => null
});

window.ResizeObserver = jest.fn().mockImplementation(() => ({
  observe: () => null,
  unobserve: jest.fn(),
  disconnect: jest.fn(),
}))


describe('BarChart component', () => {
  
  jest.mock('use-resize-observer', () => ({
    __esModule: true,
    default: jest.fn().mockImplementation(() => ({
      observe: () => null, // jest.fn()
      unobserve: jest.fn(),
      disconnect: jest.fn(),
    })),
  }));
  test('renders bar chart with correct labels and counts', () => {
    

    const anyGlobal = global as any;

    const ResizeObserverMock = jest.fn(() => ({
      observe: jest.fn(),
      unobserve: jest.fn(),
      disconnect: jest.fn(),
    }));

    const elements = [
      { id: '1', title: 'element 1', desc: 'description 1', gravity: 10 },
      { id: '2', title: 'element 2', desc: 'description 2', gravity: 10 },
      { id: '3', title: 'element 3', desc: 'description 3', gravity: 10 },
      { id: '4', title: 'element 4', desc: 'description 4', gravity: 15 },
      { id: '5', title: 'element 5', desc: 'description 5', gravity: 15 },
    ];

    render(<BarChart elements={elements} />); 


    // Verify chart labels
    const chart = screen.getByTestId('bar-chart');
    const labels = chart.getElementsByTagName('text');
    expect(labels[0].textContent).toBe('10');
    expect(labels[1].textContent).toBe('15');

    // Verify chart counts
    const bars = chart.getElementsByClassName('bar');
    expect(bars[0].getAttribute('aria-label')).toBe('3');
    expect(bars[1].getAttribute('aria-label')).toBe('2');
  });

  test('destroys previous chart instance when elements change', () => {
    const elements1 = [
      { id: '1', title: 'Element 1', desc: 'Description 1', gravity: 10 },
      { id: '2', title: 'Element 2', desc: 'Description 2', gravity: 10 },
    ];

    const { rerender } = render(<BarChart elements={elements1} />);

    // Mock the destroy method of chart instance
    const destroySpy = jest.fn();
    const elements2 = [
      { id: '3', title: 'Element 3', desc: 'Description 3', gravity: 15 },
    ];

    rerender(<BarChart elements={elements2} />);

    expect(destroySpy).toHaveBeenCalled();
  });
});
