// jest-dom adds custom jest matchers for asserting on DOM nodes.
// allows you to do things like:
// expect(element).toHaveTextContent(/react/i)
// learn more: https://github.com/testing-library/jest-dom
import '@testing-library/jest-dom';
global.ResizeObserver = require('resize-observer-polyfill')
jest.mock('use-resize-observer', () => ({
    __esModule: true,
    default: jest.fn().mockImplementation(() => ({
      observe: () => null, // jest.fn()
      unobserve: jest.fn(),
      disconnect: jest.fn(),
    })),
  }));
  global.ResizeObserver = jest.fn().mockImplementation(() => ({
    observe: () => null,
    unobserve: jest.fn(),
    disconnect: jest.fn(),
}))