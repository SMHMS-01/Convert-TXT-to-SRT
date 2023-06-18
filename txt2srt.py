# Convert txt file with timestamp to SRT file

TXT_FILE_PATH = '.'
TXT_FILE_NAME = 'Yanis Varoufakis & Slavoj Zizek _ Festival INDIGO 2021'
txt_file_path = f"{TXT_FILE_NAME}.txt"
srt_file_path = f"{TXT_FILE_NAME}.srt"


def convert_txt_to_srt(txt_file_path=txt_file_path, srt_file_path=srt_file_path):
    with open(txt_file_path, 'r', encoding='utf-8-sig') as txt_file:
        lines = txt_file.readlines()

    srt_lines = []
    line_number = 1
    for line in lines:
        line = line.strip()
        if line:
            if line.startswith('['):
                line = line[1:]  # Remove leading '['
            timestamp_end_index = line.find(']')
            timestamp = line[:timestamp_end_index].strip()
            subtitle = line[timestamp_end_index+1:].strip()
            # Convert format 00:00:00.000,00:00:15.0000 to 00:00:00,000 --> 00:00:15,000
            timestamp = timestamp.replace('.', ',') + '0'
            srt_lines.append(str(line_number))
            srt_lines.append(timestamp)
            srt_lines.append(subtitle)
            srt_lines.append('')
            line_number += 1

    with open(srt_file_path, 'w', encoding='utf-8') as srt_file:
        srt_file.write('\n'.join(srt_lines))

    print(f"Conversion successful. SRT file created: {srt_file_path}")


if __name__ == "__main__":
    convert_txt_to_srt()
