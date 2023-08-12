#!/bin/bash

# Read domain names from input file
input_file="$1"
domain_names=$(cat $input_file)

ip_addresses=()

for domain_name in $domain_names
do
    ip_address=$(dig +short $domain_name)

    ip_addresses+=("$ip_address")
done

echo "IP addresses:"
printf '%s\n' "${ip_addresses[@]}"
