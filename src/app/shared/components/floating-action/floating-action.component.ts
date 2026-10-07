import {
  ChangeDetectionStrategy,
  Component,
} from '@angular/core';

@Component({
  selector: 'app-floating-action',
  standalone: true,
  templateUrl: './floating-action.component.html',
  styleUrl: './floating-action.component.scss',
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class FloatingActionComponent {}
