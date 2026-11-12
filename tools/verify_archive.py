#!/usr/bin/env python3
"""Read-only integrity check for the self-contained RDMA research archive."""
from pathlib import Path
from html.parser import HTMLParser
from urllib.parse import urlsplit, unquote
import hashlib, json, struct
R=Path(__file__).resolve().parents[1]
class Page(HTMLParser):
 def __init__(self):super().__init__();self.ids=[];self.refs=[];self.images=[];self.papers=0;self.figures=0
 def handle_starttag(self,tag,attrs):
  a=dict(attrs)
  if a.get('id'):self.ids.append(a['id'])
  for attr in ('href','src'):
   if a.get(attr):self.refs.append(a[attr])
  if tag=='article' and 'paper' in a.get('class','').split():self.papers+=1
  if tag=='figure':self.figures+=1
  if tag=='img' and a.get('src'):self.images.append(a)
pages={};errors=[]
for rel in ['index.html']+[str(p.relative_to(R)) for p in sorted(R.glob('20??-??-??/index.html'))]:
 f=R/rel;text=f.read_text();p=Page();p.feed(text);pages[f.resolve()]=p
 if text.lower().count('<!doctype')!=1:errors.append(rel+': DOCTYPE count')
 if len(p.ids)!=len(set(p.ids)):errors.append(rel+': duplicate IDs')
 if rel!='index.html' and p.papers != (3 if rel.startswith('2026-11-12') else 5):errors.append(rel+': unexpected paper count')
for f,p in pages.items():
 for ref in p.refs:
  u=urlsplit(ref)
  if u.scheme or u.netloc:continue
  target=(f.parent/unquote(u.path)).resolve() if u.path else f
  if not target.is_file():errors.append(str(f.relative_to(R))+': broken reference '+ref);continue
  if u.fragment and target.suffix=='.html':
   q=pages.get(target)
   if not q:q=Page();q.feed(target.read_text())
   if unquote(u.fragment) not in q.ids:errors.append(str(f.relative_to(R))+': missing anchor '+ref)
 for a in p.images:
  image=(f.parent/a['src']).resolve()
  if not a.get('alt'):errors.append(str(image)+': missing alt')
  if image.is_file() and image.suffix=='.png':
   width,height=struct.unpack('>II',image.read_bytes()[16:24])
   if (str(width),str(height))!=(a.get('width'),a.get('height')):errors.append(str(image)+': dimension mismatch')
figs=json.loads((R/'figure-sources.json').read_text())['figures']
if sum(p.figures for p in pages.values())!=len(figs):errors.append('figure count mismatch')
for f in figs:
 if not f.get('analysis_zh') or not f.get('author_credit') or not f.get('source_url'):errors.append('incomplete attribution '+str(f))
 if not (R/f['archive_path']).is_file():errors.append('missing excerpt '+f['archive_path'])
for f in R.rglob('mechanism.*'):errors.append('legacy diagram remains '+str(f))
for f in R.rglob('*.pdf'):errors.append('full PDF must not be republished '+str(f))
manifest=R/'manifest.json'
if manifest.exists():
 listed=json.loads(manifest.read_text())['files'];expected={x['path'] for x in listed}
 actual={str(f.relative_to(R)) for f in R.rglob('*') if f.is_file() and '.git' not in f.parts and f.name not in ('manifest.json','SHA256SUMS.txt')}
 if expected!=actual:errors.append('manifest file set mismatch')
 for x in listed:
  f=R/x['path']
  if f.is_file() and (f.stat().st_size!=x['bytes'] or hashlib.sha256(f.read_bytes()).hexdigest()!=x['sha256']):errors.append('manifest checksum mismatch '+x['path'])
print(json.dumps({'pages':len(pages),'papers':sum(p.papers for p in pages.values()),'figures':len(figs),'errors':errors},ensure_ascii=False,indent=2))
raise SystemExit(bool(errors))
