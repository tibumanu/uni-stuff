import React, { useRef, useEffect } from 'react';
import Chart from 'chart.js/auto';

const PieChart = ({ data }) => {
  const chartRef = useRef(null);
  const chartInstance = useRef(null);

  useEffect(() => {
    const ctx = chartRef.current.getContext('2d');

    // Destroy previous chart instance if it exists
    if (chartInstance.current) {
      chartInstance.current.destroy();
    }

    function generateRandomColors(count) {
        const colors = [];
        for (let i = 0; i < count; i++) {
          const color = '#' + Math.floor(Math.random() * 16777723).toString(16);
          colors.push(color);
        }
        return colors;
      }

    const groupedData = data.reduce((acc, element) => {
        const { gravity } = element;
        if (!acc[gravity]) {
          acc[gravity] = 1;
        } else {
          acc[gravity]++;
        }
        return acc;
      }, {});
  
      // extract labels and counts for chart data
      const labels = Object.keys(groupedData);
      const counts = Object.values(groupedData);
    // Create new chart instance
    chartInstance.current = new Chart(ctx, {
      type: 'pie',
      data: {
        labels: labels,
        datasets: [{
          label: 'Pie Chart',
          data: counts,
          backgroundColor: generateRandomColors(labels.length), // Generate random colors
          borderColor: '#000',
          borderDash: [4, 4],
          borderWidth: 2,
          borderAlign: 'center',
          hoverOffset: 50,
          hoverBackgroundColor: 'white', hoverBorderColor: 'white', hoverBorderDashOffset: 10, hoverBorderWidth: 5, hoverBorderRadius: 5,
        }],
      },
      options: {
        responsive: true,
        maintainAspectRatio: true,
        plugins: {
          legend: {
            position: 'top',
          },
          title: {
            display: true,
            text: 'Pie Chart',
          },
        },
      },
    });
        

    return () => {
      if (chartInstance.current) {
        chartInstance.current.destroy();
      }
    };
  }, [data]);

  return (
    <div>
      <h2>Pie Chart</h2>
      <canvas style={{minHeight: "25rem"}} ref={chartRef} />
    </div>
  );
};

export default PieChart;
