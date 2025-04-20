#!/usr/bin/env python3

import os
import re
import matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict

def parse_results():
    results = defaultdict(lambda: defaultdict(dict))
    
    # Regular expressions to extract statistics
    hit_rate_pattern = r"Hit Rate: (\d+\.\d+)"
    avg_latency_pattern = r"Average Memory Access Latency: (\d+\.\d+)"
    
    # Process each result file
    for filename in os.listdir('../results'):
        if not filename.endswith('.txt'):
            continue
            
        # Extract configuration and trace name
        parts = filename.split('_')
        config = '_'.join(parts[:-1])
        trace = parts[-1].replace('.txt', '')
        
        with open(f'../results/{filename}', 'r') as f:
            content = f.read()
            
            # Extract hit rate
            hit_rate_match = re.search(hit_rate_pattern, content)
            if hit_rate_match:
                results[config][trace]['hit_rate'] = float(hit_rate_match.group(1))
            else:
                print(f"Warning: Could not find hit rate in {filename}")
                continue
                
            # Extract average latency
            latency_match = re.search(avg_latency_pattern, content)
            if latency_match:
                results[config][trace]['latency'] = float(latency_match.group(1))
            else:
                print(f"Warning: Could not find latency in {filename}")
                continue
    
    return results

def plot_hit_rates(results):
    plt.figure(figsize=(12, 6))
    
    # Get unique configurations and traces
    configs = sorted(results.keys())
    traces = sorted(set(trace for config in results.values() for trace in config.keys()))
    
    # Prepare data
    x = np.arange(len(traces))
    width = 0.8 / len(configs)
    
    for i, config in enumerate(configs):
        hit_rates = []
        for trace in traces:
            if trace in results[config] and 'hit_rate' in results[config][trace]:
                hit_rates.append(results[config][trace]['hit_rate'])
            else:
                hit_rates.append(0)  # Default value if data is missing
        plt.bar(x + i*width, hit_rates, width, label=config)
    
    plt.xlabel('Trace Files')
    plt.ylabel('Hit Rate (%)')
    plt.title('Cache Hit Rates by Configuration')
    plt.xticks(x + width*(len(configs)-1)/2, traces, rotation=45)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.tight_layout()
    plt.savefig('../results/hit_rates.png')
    plt.close()

def plot_latencies(results):
    plt.figure(figsize=(12, 6))
    
    # Get unique configurations and traces
    configs = sorted(results.keys())
    traces = sorted(set(trace for config in results.values() for trace in config.keys()))
    
    # Prepare data
    x = np.arange(len(traces))
    width = 0.8 / len(configs)
    
    for i, config in enumerate(configs):
        latencies = []
        for trace in traces:
            if trace in results[config] and 'latency' in results[config][trace]:
                latencies.append(results[config][trace]['latency'])
            else:
                latencies.append(0)  # Default value if data is missing
        plt.bar(x + i*width, latencies, width, label=config)
    
    plt.xlabel('Trace Files')
    plt.ylabel('Average Memory Access Latency (cycles)')
    plt.title('Memory Access Latency by Configuration')
    plt.xticks(x + width*(len(configs)-1)/2, traces, rotation=45)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.tight_layout()
    plt.savefig('../results/latencies.png')
    plt.close()

def main():
    # Create results directory if it doesn't exist
    os.makedirs('../results', exist_ok=True)
    
    # Parse results
    results = parse_results()
    
    if not results:
        print("Error: No valid results found to plot")
        return
    
    # Generate plots
    plot_hit_rates(results)
    plot_latencies(results)
    
    print("Plots generated in results directory")

if __name__ == "__main__":
    main() 