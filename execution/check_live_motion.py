"""Observe optional smooth swing in the actual production PBW, then restore defaults."""
from pathlib import Path
import argparse,json,time,shutil
from PIL import Image
from capture_native import ROOT,OUT,command,capture,monitors,close

def main():
 p=argparse.ArgumentParser();p.add_argument('--platform',choices=['emery','gabbro'],required=True);p.add_argument('--reset-emulator',action='store_true');a=p.parse_args();platform=a.platform
 for port in monitors().values():close(port)
 command(['pebble','kill'])
 if a.reset_emulator:
  sdk=Path.home()/'Library/Application Support/Pebble SDK'
  for flash in sdk.glob('*/*/*flash*.bin'):
   backup=OUT/'emulator-backups'/flash.relative_to(sdk);backup.parent.mkdir(parents=True,exist_ok=True)
   if not backup.exists():shutil.copy2(flash,backup)
  command(['pebble','wipe'])
 pbw=ROOT/'dist/Pendulum-0.1.0.pbw';install=['pebble','install','--emulator',platform,str(pbw)];command(install);command(install)
 keys=json.loads((ROOT/'watchface/build/js/message_keys.json').read_text());uuid=json.loads((ROOT/'watchface/package.json').read_text())['pebble']['uuid']
 def send(values):command(['pebble','send-app-message','--emulator',platform,'--app-uuid',uuid,'--int']+[f'{keys[k]}={v}' for k,v in values.items()])
 try:
  send({'Palette':0,'TimeFormat':2,'DateFormat':0,'Labels':1,'DigitalTime':1,'SmoothMotion':1})
  reference=Image.open(ROOT/f'media/{platform}-default.png').convert('RGB');w,h=reference.size;header=(w//2-31,5,w//2+31,18);expected=reference.crop(header).tobytes();frames=[];positions=[]
  for i in range(18):
   time.sleep(.11);im=capture()
   if im.crop(header).tobytes()!=expected:continue
   points=[(x,y) for y in range(165 if w==260 else 145,235 if w==260 else 205) for x in range(w//2-40,w//2+41) if im.getpixel((x,y))==(85,255,255)]
   if len(points)<100:continue
   cx=sum(x for x,y in points)/len(points);positions.append(round(cx,1));frames.append(im.copy())
  assert len(frames)>=8,'Expected complete production frames';assert len(set(round(x) for x in positions))>=5,'Smooth swing did not show intermediate positions';assert max(positions)-min(positions)>8,'Insufficient live swing range'
  frames[0].save(ROOT/f'media/{platform}-live-swing.gif',save_all=True,append_images=frames[1:],duration=110,loop=0,disposal=2,optimize=False)
 finally:
  try:send({'SmoothMotion':0,'TimeFormat':0})
  finally:command(['pebble','kill'])
 report={'platform':platform,'production':True,'complete_frames':len(frames),'bob_centroid_x':positions,'intermediate_positions_observed':True,'defaults_restored':True};(OUT/f'{platform}-live-motion.json').write_text(json.dumps(report,indent=2)+'\n');print('LIVE MOTION PASS',platform,positions)
if __name__=='__main__':main()
