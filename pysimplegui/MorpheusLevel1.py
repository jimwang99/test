
import PySimpleGUI as sg

################################################################
# address map table window


class SGTable:
    def __init__(self, num_row, num_col, key='table'):
        self.num_row = num_row
        self.num_col = num_col
        self.key = key
        self.layout = list()

        self.header = ['header %d' % ii for ii in range(num_col)]
        self.layout.append(self.header)

        for ii in range(num_row):
            row = list()
            for jj in range(num_col):
                key = '-%s-%d-%d-' % (key, ii, jj)
                row.append(sg.Text('', size=(20,1), pad=(0,0), key=key))
            self.layout.append(row)

################################################################

table_addr_map = SGTable(3, 5, key='addr_map')

layout_main = [
        [sg.Text("Components")],
        [sg.Text("  - RISC-V CPU"), sg.DropDown(('1'))]
    ]

layout_top = [
        [sg.TabGroup([[
            sg.Tab('Main', layout_main),
            sg.Tab('Address Map', layout_main),
            ]])
        ],
        [[sg.Button('Check')], [sg.Button('Save')], [sg.Button('Cancel')]]
    ]

window_top = sg.Window('Morpheus Level 1: Configuration Creator', layout_top, font='Courier New 12')

while True:
    event, values = window_top.Read(timeout=1000)
    if (event in (None, 'Cancel')):
        break
