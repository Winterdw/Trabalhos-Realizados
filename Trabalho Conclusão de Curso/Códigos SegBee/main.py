import kivy
import sys
import os
import time
import SegmentadorDeMel as seg
from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.properties import ObjectProperty
from kivy.uix.popup import Popup
from kivy.uix.widget import Widget
from kivy.uix.button import Button

class LoadDialog(FloatLayout):
    load = ObjectProperty(None)
    cancel = ObjectProperty(None)
    
class Tela1(BoxLayout):

    loadfile = ObjectProperty(None)
 
    def dismiss_popup(self):
        self._popup.dismiss()
 
    def show_load(self):
        content = LoadDialog(load=self.load, cancel=self.dismiss_popup)
        self._popup = Popup(title="Ler Arquivo", content=content,size_hint=(0.9, 0.9))
        self._popup.open()
 
     
    def load(self, path, filename):
        with open(os.path.join(path, filename[0])) as stream:
            self.text_input.text = stream.read()
            self.text_input.cursor=0,0
        self.dismiss_popup()
       
    def on_press_bt(self):
        janela.root_window.remove_widget(janela.root)
        janela.root_window.add_widget(Tela2())

    def on_press_bt2(self):
        janela.root_window.remove_widget(janela.root)
        janela.root_window.add_widget(Tela2())

    def on_press_bt3(self):
        janela.stop()

class Tela2(BoxLayout):
kv='''
BoxLayout:
    orientation: 'vertical'
    Camera:
        id: camera
        resolution: 1920, 1080
    BoxLayout:
        orientation: 'horizontal'
        size_hint_y: None
        height: '48dp'
        Button:
            markup: True
            text: '[b][color=#0000]start[/b][/color]'
            on_release: camera.play = True
        Button:
            text: 'Fechar'
            on_release:
                camera.play = False
                app.save_picture(camera.texture)
                janela.root_window.remove_widget(janela.root)
                janela.root_window.add_widget(Tela1())
        Button:
            text: 'PrintScr'
            on_release: app.print_scr()
'''
class CameraApp(App):
    def build(self):
        return Builder.load_string(kv)

    def save_picture(self, picture):
        img = Image(picture)
        img.save('foto01.jpg')
    def print_scr(self, *largs):
        Window.screenshot(name='foto02.jpg')
  
class Bibkivy(App):
    pass
    
janela = Bibkivy()
janela.run()