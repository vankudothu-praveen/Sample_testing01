import {
  ChangeDetectionStrategy,
  Component,
  Input,
} from '@angular/core';

@Component({
  selector: 'app-greeting-header',
  standalone: true,
  templateUrl: './greeting-header.component.html',
  styleUrl: './greeting-header.component.scss',
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class GreetingHeaderComponent {
  @Input() userName = '';
  @Input() greetingMessage = '';
  @Input() avatarInitials = '';
}
