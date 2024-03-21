#include "arp.h"

static struct arp_cache_entry arp_cache[ARP_CACHE_LEN];

void arp_init(){
    memset(arp_cache, 0, ARP_CACHE_LEN * sizeof(struct arp_cache_entry));
}

void arp_incoming(int tun_fd, struct eth_hdr* hdr) {
    // printf("Found ARP\n");
    struct arp_hdr* arp_header;
    struct arp_ipv4* arp_payload;
    int merge_flag = 0;

    arp_header = (struct arp_hdr*) hdr->payload;
    arp_header->hw_type = htons(arp_header->hw_type);
    arp_header->pro_type = htons(arp_header->pro_type);
    arp_header->opcode = htons(arp_header->opcode);

    if (arp_header->hw_type != ARP_ETHERNET)
    {
        printf("Unsupported HW type\n");
        return;
    }
    if (arp_header->pro_type != ARP_IPV4)
    {
        printf("Unsupported protocol\n");
        return;
    }
    
    arp_payload = (struct arp_ipv4*) arp_header->payload;
    
    // if (arp_header->opcode == ARP_REQUEST)
    // {
    //     printf("Detected ARP request\n");
    // }
    update_arp_translation_table(arp_header, arp_payload);
    switch (arp_header->opcode)
    {
    case ARP_REQUEST:
        break;
    default:
        printf("Opcode not supported\n");
        break;
    }
}

int update_arp_translation_table(struct arp_hdr *hdr, struct arp_ipv4 *data)
{
    struct arp_cache_entry *entry;

    for (int i = 0; i<ARP_CACHE_LEN; i++) {
        entry = &arp_cache[i];

        if (entry->state == ARP_FREE) continue;

        if (entry->hw_type == hdr->hw_type && entry->src_addr == data->src_addr) {
            memcpy(entry->src_mac, data->src_mac, 6);
            return 1;
        }
    }
    
    return 0;
}