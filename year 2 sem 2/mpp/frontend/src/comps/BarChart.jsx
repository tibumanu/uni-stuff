import React, { useRef, useEffect } from 'react';
import Chart from 'chart.js/auto';
import { ResizeObserver } from '@juggle/resize-observer';


const BarChart = ({ elements }) => {
  const chartRef = useRef(null);
  const chartInstance = useRef(null);

  useEffect(() => {
    const ctx = chartRef.current.getContext('2d');

    // destroy previous chart instance if it exists
    if (chartInstance.current) {
      chartInstance.current.destroy();
    }
    // return () => {
    //   if (chartInstance.current && typeof chartInstance.current.destroy === 'function') {
    //     chartInstance.current.destroy();
    //   }
    // };

    // // group elements by gravity
    // const groupedData = elements.reduce((acc, element) => {
    //   const { gravity } = element;
    //   if (!acc[gravity]) {
    //     acc[gravity] = 1;
    //   } else {
    //     acc[gravity]++;
    //   }
    //   return acc;
    // }, {});

    // fetch from http://localhost:5000/api/elements/chartdata
    const fetchChartData = async () => {
      try {
        const response = await fetch('http://localhost:5000/api/elements/chartdata');
        console.log(response);
        if (!response.ok) {
          throw new Error('Failed to fetch data');
        }
        const data = await response.json();
        return data;
      } catch (error) {
        console.error(error);
      }
    };

    // extract labels and counts for chart data
    const labels = Object.keys(fetchChartData);
    const counts = Object.values(fetchChartData);

    // create new chart instance
    chartInstance.current = new Chart(ctx, {
      type: 'bar',
      id: 'bar-chart',
      data: {
        labels,
        datasets: [{
          label: 'Element Count by Gravity',
          data: counts,
          backgroundColor: 'rgba(75, 192, 192, 0.2)',
          borderColor: 'rgba(75, 192, 192, 1)',
          borderWidth: 3,
          borderRadius: 15,
          hoverBorderColor: 'rgba(75, 192, 192, 1)',
          hoverBorderWidth: 5,
          hoverBackgroundColor: 'rgba(75, 192, 192, 0.4)',
          hoverBorderRadius: 10,
        }]
      },
      options: {
        responsive: true,
        maintainAspectRatio: true,
        scales: {
          y: {
            beginAtZero: true,
            title: {
              display: true,
              text: 'Count'
            }
          },
          x: {
            title: {
              display: true,
              text: 'Gravity'
            }
          }
        }
      }
    });

    // Clean up chart instance when component unmounts
    return () => {
      if (chartInstance.current) {
        chartInstance.current.destroy();
      }
    };
  }, [elements]);

  // Return JSX element
  return (
    <div>
      <h2>Bar Chart</h2>
      <canvas style={{minHeight: "25rem"}}ref={chartRef} data-testid="bar-chart" />
    </div>
  );
};

export default BarChart;
